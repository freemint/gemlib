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
 * Description:
 *   The goal of this function is to provide cicon server (24 bit true color for MyAES or 32 picture)
 *   This function provide only CICON data with bitmap and mask and not a full object icon. 
 *   Data provide by this function should be relocated and copy, AES not keep in memory CICON block provided that should be copy.
 *
 * type&0xFF:
 *
 *  0 : 	Application icon
 *  1 : 	File extension icon
 *  2 : 	Reserved
 *  3 : 	Load PNG file as icon from specific path
 *  4 : 	Other icon (any other specific icon)
 *
 * if type&0x100 =0 cicon_data return a CICON block as need by AES for display color icon
 *                  else cicon_data return a simple bitmap block in ARBG format with 8 bit transparency
 *                 (this format is not recognize by AES)
 *
 * name 	name of the cicon to load, some exemple:
 *              with type&0xFF:
 *   0 : 	name = "purec"
 *   1 : 	name = "html"
 *   3 : 	name = "C:\myprog\mypng\pngname.png"
 *   4 : 	name = "computer"
 *
 * size 	Size of the cicon to load, there is 3 different case:
 *        size > 0 	is the size of the icon requested and should be a multiple of 16
 *        size = 0 	the default cicon size is requested and is set by aes configuration
 *        size = -1 	the return cicon can be of any size and can change from a cicon to another
 *
 * cicon_data 	Return block of type CICON + mask + icon bitmap if type&0x100 = 0
 *              else a bitmap 32 bit with alpha chanel in the format ARGB 8 bits per chanel.
 *
 *      Relocation of cicon_data, cicon_data provide CICON block + mask + bitmap
 *
 *
 *      num_planes : number of planes

 *      *col_data, *col_mask, *sel_data, *sel_mask: provide relative position from the start of cicon_data
 *         and should be relocated
 *
 *
 *   As the block can be free by the AES you should copy the block for your need, the size of the block to copy is:
 *
 *   number_of_block = 0
 *   if(cicon_data->col_data) number_of_block++;
 *   if(cicon_data->col_mask) number_of_block++;
 *   if(cicon_data->sel_data) number_of_block++;
 *   if(cicon_data->sel_mask) number_of_block++;
 *
 *   size = sizeof(CICON) + (cicon_data->num_planes * cicon_width * cicon_height * number_of_block)/8 + cicon_width*cicon_height;
 *
 *   CICON *newcicon;
 *   newcicon = malloc(size);
 *   memcpy(newcicon,cicon_data);
 *   if(cicon_data->col_data) newcicon->col_data += newcicon;
 *   if(cicon_data->col_mask) newcicon->col_mask += newcicon;
 *   if(cicon_data->sel_data) newcicon->sel_data += newcicon;
 *   if(cicon_data->sel_mask) newcicon->sel_mask += newcicon;
 *
 * WARNING : In the case of 32 bits bitmap requested size of the bloc = cicon_width * cicon_height * 4
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
