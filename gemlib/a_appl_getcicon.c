#include "gem_aesP.h"

/** returns information about the AES.
 *
 *  @param type  : kind of icon type and format output
 *  @param name : name of the color icon
 *  @param size : size of icon
 *  @param cicon_width : return pixel width
 *  @param cicon_height : return pixel height
 *  @param cicon_data : return CICON block + mask + icon bitmap
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since Available since MyAES 0.96 beta1
 *
 *  @sa mt_appl_getcicon()
 *
 * some more explanation:
 *
 * Description:\n
 *   The goal of this function is to provide cicon server (24 bit true color for MyAES or 32 picture)\n
 *   This function provide only CICON data with bitmap and mask and not a full object icon. \n
 *   Data provide by this function should be relocated and copy, AES not keep in memory CICON block provided that should be copy.\n
 *
 * \a type&0xFF:\n
 *
 * \a 0 : 	Application icon\n
 * \a 1 : 	File extension icon\n
 * \a 2 : 	Reserved\n
 * \a 3 : 	Load PNG file as icon from specific path\n
 * \a 4 : 	Other icon (any other specific icon)\n
 *\n
 * if \a type&0x100 =0 cicon_data return a CICON block as need by AES for display color icon
 *                  else cicon_data return a simple bitmap block in ARBG format with 8 bit transparency
 *                 (this format is not recognize by AES)\n
 *\n
 * \a name: 	name of the cicon to load, some exemple:\n
 *              with \a type&0xFF:\n
 *  \a 0 : 	name = "purec"\n
 *  \a 1 : 	name = "html"\n
 *  \a 3 : 	name = "C:\myprog\mypng\pngname.png"\n
 *  \a 4 : 	name = "computer"\n
 *\n
 * \a size 	Size of the cicon to load, there is 3 different case:\n
 *        \a size > 0 	is the size of the icon requested and should be a multiple of 16\n
 *        \a size = 0 	the default cicon size is requested and is set by aes configuration\n
 *        \a size = -1 	the return cicon can be of any size and can change from a cicon to another\n
 *\n
 * \a cicon_data 	Return block of type CICON + mask + icon bitmap if type&0x100 = 0
 *              else a bitmap 32 bit with alpha chanel in the format ARGB 8 bits per chanel.\n
 *\n
 *      Relocation of cicon_data, cicon_data provide CICON block + mask + bitmap\n
 *\n
 *\n
 *      \a num_planes : number of planes\n
 *      \a *col_data, \a *col_mask, \a *sel_data, \a *sel_mask: provide relative position from the start of cicon_data
 *         and should be relocated\n
 *\n
 *\n
 *   As the block can be free by the AES you should copy the block for your need, the size of the block to copy is:\n
 *\n
 *   number_of_block = 0\n
 *   if(cicon_data->col_data) number_of_block++;\n
 *   if(cicon_data->col_mask) number_of_block++;\n
 *   if(cicon_data->sel_data) number_of_block++;\n
 *   if(cicon_data->sel_mask) number_of_block++;\n
 *
 *   size = sizeof(CICON) + (cicon_data->num_planes * cicon_width * cicon_height * number_of_block)/8 + cicon_width*cicon_height;\n
 *\n
 *   CICON *newcicon;\n
 *   newcicon = malloc(size);\n
 *   memcpy(newcicon,cicon_data);\n
 *   if(cicon_data->col_data) newcicon->col_data += newcicon;\n
 *   if(cicon_data->col_mask) newcicon->col_mask += newcicon;\n
 *   if(cicon_data->sel_data) newcicon->sel_data += newcicon;\n
 *   if(cicon_data->sel_mask) newcicon->sel_mask += newcicon;\n
 *\n
 * WARNING : In the case of 32 bits bitmap requested size of the bloc = cicon_width * cicon_height * 4\n
 *
 *
 */


short 
mt_appl_get_cicon(short type,const char *name,short size,short *cicon_width,short *cicon_height,CICON **cicon_data, short *global_aes)
{	
	AES_PARAMS(131,2,3,1,1);

	aes_intin[0] = type;
	aes_intin[1] = size;
	aes_addrin[0] = (long )name;
	aes_addrout[0] = (long )cicon_data;
	AES_TRAP(aes_params);

	*cicon_width = aes_intout[1];
	*cicon_height = aes_intout[2];

	return (aes_intout[0]);
}
