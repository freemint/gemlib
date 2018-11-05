/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** list box - create
 *
 *  @param tree Pointer to the object tree of the dialog
 *  @param slct Pointer to selection routine
 *  @param set Pointer to set routine
 *  @param items Pointer to linked list with LBOX_ITEMs.
 *		   The pointer \p items can also be 0L if the list box is still empty and does
 *		   not contain any entries.
 *  @param visible_a Number of visible entries (Slider A)
 *  @param first_a Index of the first visible entry (Slider A)
 *  @param ctrl_objs Pointer to a field with the object numbers
 *		   of the buttons and slider (5 entries)
 *  @param objs Pointer to a field with the object numbers
 *		   of the list box items (\p entries entries)
 *  @param flags Various flags:
 *         -   LBOX_VERT   (1)	 List box with vertical slider 
 *         -   LBOX_AUTO   (2)	   Auto scrolling
 *         -   LBOX_AUTOSLCT  (4)    Automatic display during auto scrolling
 *         -   LBOX_REAL   (8)	   Real-time slider 
 *         -   LBOX_SNGL   (16)	   Only one selectable entry 
 *         -   LBOX_SHFT   (32)	   Multiple selections with Shift 
 *         -   LBOX_TOGGLE (64)	   On selection change status of an entry 
 *         -   LBOX_2SLDRS (128)     Support 2 sliders 
 *         .
 *		   The flag LBOX_SNGL can also be combined with LBOX_SHFT or LBOX_TOGGLE
 *		   to permit deselection in a list box with only one selectable entry.
 *		   LBOX_SNGL + LBOX_SHFT means that the selected entry can be deselected
 *		   by a click with a pressed Shift key. LBOX_SNGL + LBOX_TOGGLE causes a
 *		   click to deselect a selected entry.
 *  @param pause_a Delay during scrolling in ms (Slider A)
 *  @param user_data Pointer for application
 *  @param dialog Pointer to the window dialog structure or 0L
 *  @param visible_b Number of visible items (Slider B)
 *  @param first_b First visible item (Slider B)
 *  @param entries_b Number of items (Slider B)
 *  @param pause_b Delay during scrolling in ms (Slider B)
 *  @param global_aes global AES array
 *
 *  @return Pointer to the list box structure or 0L
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 *  This function allocates memory for a list box and initialises the 
 *  objects by calling the routine \p set for each object passed in \p objs. 
 *  However the list box will not be drawn!
 *  
 *  Bit 0 of the variable \p flags determines whether the list box is a 
 *  horizontal one (the first list item at left and last at right) or a 
 *  vertical one (the first list item at top and last at bottom).
 *  Independently of this main scrolling direction the list box can also 
 *  have a second slider if the items themselves are to be scrolled. This 
 *  can be sensible, for instance, with a vertical list box with text items 
 *  that are wider than the box.
 *  
 *  Both \p slct and \p set are functions whose parameters are passed on the 
 *  stack. The functions may alter registers d0-d2/a0-a2.
 *  
 *  \p slct is a pointer to a selection routine that is always called when 
 *  an entry is selected or deselected:
 *
\verbatim
typedef void (cdecl *SLCT_ITEM)( LIST_BOX *box, OBJECT *tree,
                                 struct _lbox_item *item,
                                 void *user_data,
                                 WORD obj_index, WORD last_state );
\endverbatim
 *  - \p box   points to the list box structure
 *  - \p tree  	  points to the object tree of the dialog
 *  - \p item  	  points to the LBOX_ITEM-structure of the selected entry
 *  - \p user_data   is the pointer passed by mt_lbox_create()
 *  - \p obj_index   is the number of the selected object. For a double-click the 
 * 		  top bit is set, similar to mt_form_do(). If is 0 it signifies 
 * 		  that no object is assigned to this entry; it is not visible. 
 * 		  Normally this only the case when one is scrolling and by 
 * 		  selecting a new object the (now no longer visible) selection 
 * 		  has to be cleared.
 *  - \p last_state  is the previous status of the object.  can also have the 
 * 		  same value as selected>. In that case one can normally quit 
 * 		  the function immediately.
 * 
 *	\p slct will also be called when the selection of an object is cleared!
 *	The variable \p selected from the LBOX_ITEM structure already contains
 *	the new status of the object when \p slct is called.
 *	
 *	\p set points to the function that is to enter the contents of a 
 *	LBOX_ITEM into an object of the list box dialog:
 *	
\verbatim
typedef WORD (cdecl *SET_ITEM)( LIST_BOX *box, OBJECT *tree,
                                struct _lbox_item *item,
                                WORD obj_index,
                                void *user_data, GRECT *rect,
                                WORD first );
\endverbatim
 *  - \p box        points to the list box structure
 *  - \p tree       points to the object tree of the dialog
 *  - \p item       points to the LBOX_ITEM structure of the entry to be set 
 *  - \p obj_index  is the number of the object to be set
 *  - \p user_data  is the pointer passed by mt_lbox_create()
 *  - \p rect       is the pointer to the GRECT for the object redraw or 0L
 *  - \p first      contains the number of the first visible item for Slider B
 * 
 *  For a list box that only contains text strings, \p set is typically a 
 *  function that copies a string pointed to by the LBOX_ITEM structure 
 *  into the object \p index.
 *  
 *  \p rect is 0L when a redraw of the dialog box is executed or when 
 *  mt_lbox_update() has been called.
 *  
 *  \p rect is not 0L when the user has selected or deselected an object, 
 *  and points to the GRECT for the redraw. The return value of \p set is 
 *  the number of the start object for mt_objc_draw()/mt_wdlg_redraw(). For 
 *  entries in the list box that consist of several objects it is sometimes 
 *  sensible to reduce the redraw rectangle when selecting/deselecting an 
 *  object, or to alter the start object, to prevent unnecessary drawing 
 *  operations and/or unnecessary flicker.
 *  
 *  In most cases the list box routines call the function mt_objc_draw()/
 *  mt_wdlg_redraw() after \p set to display the altered contents.
 *  
 *  \p first contains the number of the first visible item for Slider B if 
 *  the list box has two sliders. For a (vertical) list box with text 
 *  strings and two sliders, when calling mt_lbox_create(), for instance, one 
 *  enters the number of visible characters in \p visible_b, the total 
 *  string length in \p entries_b and the index of the first visible 
 *  character in \p first_b. If the text is scrolled horizontally, \p set is 
 *  called for all visible strings and the affected parts of the screen are 
 *  redrawn or moved. If the list box has only one slider, \p first is 
 *  always 0.
 *  
 *  \p items points to the first item in a list from LBOX_ITEM. The structure 
 *  used for the items must contain a pointer to its successor (next) as its 
 *  first element and a word for the condition (selected) as the second:
 *  
\verbatim
   typedef struct _lbox_item
   {
      struct _lbox_item *next;
      WORD  selected;   
      WORD  data1;      
      void  *data2;
      void  *data3;

   } LBOX_ITEM;
\endverbatim
 *  
 *  However the structure can well look like the following example with 
 *  appropriate casting during the call:
 *  
\verbatim
   typedef struct
   {
      void  *next;
      WORD  selected;

      ... From here on to suit the application ...

   } LB_EXAMPLE;
\endverbatim
 *  
 *  
 *  \p ctrl_objs is a pointer to a field with 5 or 9 entries that contains the 
 *  numbers of the control objects (buttons):
 *   - ctrl_objs[0]: Object number of the BOX or IBOX, that contains the actual 
 *  			     list box object
 *   - ctrl_objs[1]: Object number of the buttons for scrolling upwards or left
 *   - ctrl_objs[2]: Object number of the buttons for scrolling downwards or 
 *   			     right
 *   - ctrl_objs[3]: Object number of the slider background box
 *   - ctrl_objs[4]: Object number of the slider box
 *  
 *  If the list box has 2 sliders, ctrl_objs[5-8] contain the numbers of 
 *  the objects for Slider B:
 *   - ctrl_objs[5]:	Object number of the button for scrolling upwards or left
 *   - ctrl_objs[6]:	Object number of the button for scrolling downwards or right
 *   - ctrl_objs[7]:	Object number of the slider background box
 *   - ctrl_objs[8]:	Object number of the slider box
 *  
 *  The buttons, the slider and the slider background should have a 
 *  TOUCHEXIT status. If the list box contains only buttons and no slider,
 *  ctrl_objs[3/4 or 7/8] must contain -1.
 *  
 *  \p objs is a field with \p entries entries that contains the numbers of the 
 *  list box objects (the objects are normally children of ctrl_objs[0]).
 *  
 *     - objs[0]:             Number of the first object
 *     -      ...
 *     -      ...
 *     -      ...
 *     - objs[entries - 1]:   Number of the last object
 *  
 *  
 *  The objects should normally have TOUCHEXIT status.
 *  
 *  The word \p flags influences the behaviour of the list box:
<pre>
+-----+---------+-------------------------------------------------------+
| Bit |  State  | Description                                           |
+-----+---------+-------------------------------------------------------+
|  0  |   0     | The box scrolls horizontally                          |
|     |   1     | The box scrolls vertically                            |
+-----+---------+-------------------------------------------------------+
|  1  |   0     | No automatic scrolling                                |
|     |   1     | Scrolling takes place automatically as soon as the    |
|     |         | mouse cursor is moved past the first or last item     |
|     |         | with the mouse button held down                       |
+-----+---------+-------------------------------------------------------+
|  2  |   0     | The selection routine will be called only after the   |
|     |         | automatic scrolling has finished, i.e. it will be     |
|     |         | called for the last selected entry.                   |
|     |   1     | With automatic scrolling the selection routine will   |
|     |         | be called for each selected entry during scrolling    |
+-----+---------+-------------------------------------------------------+
|  3  |   0     | When moving the slider a frame will be moved          |
|     |         | (graf_slidebox), the list box will only be updated    |
|     |         | after releasing the mouse button                      |
|     |   1     | The slider is a real-time slider                      |
+-----+---------+-------------------------------------------------------+
|  4  |   0     | Multiple selections within the list box are possible  |
|     |   1     | Only one item can be selected                         |
+-----+---------+-------------------------------------------------------+
|  5  |   0     | Multiple selections possible without the Shift key    |
|     |   1     | Multiple selections only possible with the Shift key  |
+-----+---------+-------------------------------------------------------+
|  6  |   0     | On selection the status is always SELECTED            |
|     |   1     | On selection the status is always changed             |
+-----+---------+-------------------------------------------------------+
|  7  |   0     | The list box has only one slider                      |
|     |   1     | The list box has two sliders                          |
+-----+---------+-------------------------------------------------------+
</pre>
 *  
 *  
 */

LIST_BOX *
mt_lbox_create( OBJECT *tree, SLCT_ITEM slct, SET_ITEM set, LBOX_ITEM *items,
				short visible_a, short first_a, short *ctrl_objs, short *objs, short flags,
				short pause_a, void *user_data, void *dialog, short visible_b,
				short first_b, short entries_b, short pause_b, short *global_aes )
{
	AES_PARAMS(170,8,0,8,1);

	aes_intin[0]	= visible_a;
	aes_intin[1]	= first_a;
	aes_intin[2]	= flags;
	aes_intin[3]	= pause_a;
	aes_intin[4]	= visible_b;
	aes_intin[5]	= first_b;
	aes_intin[6]	= entries_b;
	aes_intin[7]	= pause_b;

	aes_addrin[0]	= (long)tree;
	aes_addrin[1]	= (long)slct;
	aes_addrin[2]	= (long)set;
	aes_addrin[3]	= (long)items;
	aes_addrin[4]	= (long)ctrl_objs;
	aes_addrin[5]	= (long)objs;
	aes_addrin[6]	= (long)user_data;
	aes_addrin[7]	= (long)dialog;
	aes_addrout[0] = 0;

	AES_TRAP(aes_params);

	return((LIST_BOX *)aes_addrout[0]);
}
