#include "gem_vdiP.h"
#include "mt_gemx.h"

/** returns extended information about the bitmap 
 *  format of the device (the device-specific format).
 *
 *  @param handle Device handle
 *  @param work_out 
 *         - work_out[0]:   pixel format
 *           - 0: interleaved planes, organized in words (ATARI)
 *           - 1: standard format (whole planes)
 *           - 2: packed pixels
 *           - (-1): unknown format; not accessible
 *         - work_out[1]:   CLUT flag
 *           - 0: no CLUT (e.g. TTM 194)
 *           - 1: hardware CLUT
 *           - 2: software CLUT (HiColor or TrueColor)
 *         - work_out[2]:   number of planes (bits) per pixel
 *         - work_out[3/4]: number of colors or 0L (more than 2*10^31 colors)
 *         - work_out[5]:   line width in bytes (since EdDI 1.1)
 *         - work_out[6/7]: address of the bitmap (since EdDI 1.1)
 *         - work_out[8]:   number of bits for red levels
 *         - work_out[9]:   number of bits for green levels
 *         - work_out[10]:  number of bits for blue levels
 *         - work_out[11]:  number of bits for alpha channel
 *         - work_out[12]:  number of bits for genlock
 *         - work_out[13]:  number of unused bits
 *         - work_out[14]:  bit order (since EdDI 1.1)
 *           - 2-256 colors:\n
\verbatim
               bit number| description
               ----------|--------------------------------------------------
                  0      | usual bit order
\endverbatim
 *           - 32768 colors (16 planes):\n
\verbatim
               bit number| description
               ----------|--------------------------------------------------
                  0      | usual bit order: 1 bit overlay (or unused),
                         | 5 bits red, 5 bits green, 5 bits blue
                         | (xrrrrrgg-gggbbbbb)
                         |
                  1      | Falcon bit order: 5 bits red, 5 bits green,
                         | 1 bit overlay, 5 bits blue
                         | (rrrrrggg-ggxbbbbb)
                         |
                  7      | swapped bytes (intel order)
                         | e.g. Crazy Dots (gggbbbbb-xrrrrrgg)
\endverbatim
 *           - 65536 colors (16 planes):
\verbatim
               bit number| description
               ----------|--------------------------------------------------
                  0      | usual bit order: 5 bits red, 6 bits green, 
                         | 5 bits blue (rrrrrggg-gggbbbbb)
                         |
                  7      | swapped bytes (intel order)
                         | e.g. Crazy Dots 2 (gggbbbbb-rrrrrggg)
\endverbatim
 *           - 16777216 colors (24 planes):
\verbatim
               bit number| description
               ----------|--------------------------------------------------
                  0      | usual bit order: 8 bits red, 8 bits green,
                         | 8 bits blue (rrrrrrrr-gggggggg-bbbbbbbb)
                         |
                  7      | swapped bytes (intel order)
                         | (bbbbbbbb-gggggggg-rrrrrrrr)
\endverbatim
 *           - 16777216 colors (32 Planes):
\verbatim
               bit number| description
               ----------|--------------------------------------------------
                  0      | usual bit order, 8 bits overlay or unused, 
                         | 8 bits red, 8 bits green, 8 bits blue
                         | (xxxxxxxx-rrrrrrrr-gggggggg-bbbbbbbb)
                         |
                  7      | swapped bytes (intel order)
                         | (bbbbbbbb-gggggggg-rrrrrrrr-xxxxxxxx)
\endverbatim
 *         . 
 *         If a hardware CLUT (intout[1] == 1) exists:
 *         - work_out[16-271]: pixel value of the corresponding VDI color index (0-255)
 *         . 
 *         In case of HiColor, TrueColor...:
 *         - work_out[16..31]:    bit number of the pixel associated with the bit number of 
 *                              the intensity level of red
 *         - work_out[32..47]:    bit number of the pixel associated with the bit number of 
 *                              the intensity level of green
 *         - work_out[48..63]:    bit number of the pixel associated with the bit number of 
 *                              the intensity level of blue
 *         - work_out[64..79]:    bit numbers for alpha channel
 *         - work_out[80..95]:    bit numbers for genlock
 *         - work_out[96..127]:   unused bits
 *         - work_out[128..271]:  reserved (0)
 *
 *  @since since EdDI 1.00
 *
 *
\verbatim
    Examples:
   ----------

   256 colors on the Falcon:

   work_out | value  | description
   ---------|--------|-----------------------------------------------------
      0     |   0    | interleaved Planes, (words)
      1     |   1    | hardware CLUT
      2     |   8    | 8 bits per pixel
      3/4   | 256    | 256 simultaneously displayable colors
      5     | xxxx   | width of the bitmap in bytes (since EdDI 1.1)
      6/7   | xxxxL  | address of the bitmap (since EdDI 1.1)
      8     |   6    | CLUT has 6 bits for red intensity
      9     |   6    | CLUT has 6 bits for green intensity
     10     |   6    | CLUT has 6 bits for blue intensity
     11     |   0    | no alpha channel
     12     |   0    | no genlock
     13     |   0    | no unused bits
     14     |   1    | usual bit order (since EdDI 1.1)
            |        |
     16     |   0    | pixel value for VDI color index 0
     17     | 255    | pixel value for VDI color index 1
     18     |   2    | pixel value for VDI color index 2
     ...    | ...    |
    271     |  15    | pixel value for VDI color index 255

   HiColor on the Falcon:

   work_out | value  | description
   ---------|--------|-----------------------------------------------------
      0     |   2    | packed pixels
      1     |   2    | HiColor (TrueColor:-) => pseudo CLUT
      2     |  16    | 16 bits per pixel
      3/4   | 32768  | 32768 colors
      5     | xxxx   | width of the bitmap in bytes (since EdDI 1.1)
      6/7   | xxxxL  | address of the bitmap (since EdDI 1.1)
      8     |   5    | 5 bits for red intensity
      9     |   5    | 5 bits for green intensity 
     10     |   5    | 5 bits for blue intensity
     11     |   0    | no alpha channel
     12     |   1    | 1 bit for genlock (overlay)
     13     |   0    | no unused bits
     14     |   2    | Falcon bit order (rrrrrggg-ggxbbbbb ; since EdDI 1.1)
            |        |
     16     |  11    | bit 0 of the red intensity (least significant bit)
            |        | is bit 11 of the pixel
     17     |  12    | bit 1 of the red intensity ist bit 12 of the pixel
     18     |  13    | ...
     19     |  14    | ...
     20     |  15    | bit 4 of the red intensity (most significant bit)
            |        | is bit 15 of the pixel
     21..31 |  -1    | bits are not used
            |        |
            |        |
     32     |   6    | bit 0 of the green intensity (least significant bit)
            |        | is bit 6 of the pixel
     33     |   7    | bit 1 of the green intensity ist bit 7 of the pixel
     34     |   8    | ...
     35     |   9    | ...
     36     |  10    | bit 4 of the green intensity (most significant bit)
            |        | is bit 10 of the pixel
     37..37 |  -1    | bits are not used
            |        |
            |        |
     48     |   0    | bit 0 of the blue intensity (least significant bit)
            |        | is bit 0 of the pixel
     49     |   1    | bit 1 of the blue intensity is bit 1 of the pixel
     50     |   2    | ...
     51     |   3    | ...
     52     |   4    | bit 4 of the blue intensity (most significant bit)
            |        | is bit 4 of the pixel
     53..63 |  -1    | bits are not used
            |        |
            |        |
     64..79 |  -1    | no alpha channel
            |        |
            |        |
     80     |   5    | bit for genlock/overlay
     81..95 |  -1    | not used
            |        |
            |        |
     96..127|  -1    | no unused bits
            |        |

   HiColor on a VGA graphic card (e.g. Crazy Dots):

   work_out | Wert   | Meaning
   ---------|--------|-----------------------------------------------------
      0     |   2    | packed pixels
      1     |   2    | HiColor => pseudo CLUT
      2     |  16    | 16 bits per pixel
      3/4   | 32768  | 32768 colors
      5     | xxxx   | width of the bitmap in bytes (since EdDI 1.1)
      6/7   | xxxxL  | address of the bitmap (since EdDI 1.1)
      8     |   5    | 5 bits for red intensity
      9     |   5    | 5 bits for green intensity 
     10     |   5    | 5 bits for blue intensity
     11     |   0    | no alpha channel
     12     |   1    | no genlock/overlay
     13     |   0    | 1 unused bits
     14     |  129   | swapped bit order (gggbbbbb-xrrrrrgg; since EdDI 1.1)
            |        |
     16     |   2    | bit 0 of the red intensity (least significant bit)
            |        | is bit 2 of the pixel
     17     |   3    | bit 1 of the red intensity is bit 3 of the pixel
     18     |   4    | ...
     19     |   5    | ...
     20     |   6    | bit 4 of the red intensity (most significant bit)
            |        | is bit 6 of the pixel
     21..31 |  -1    | bits are not used
            |        |
            |        |
     32     |  13    | bit 0 of the green intensity (least significant bit)
            |        | is bit 13 of the pixel
     33     |  14    | bit 1 of the green intensity is bit 14 of the pixel
     34     |  15    | ...
     35     |   0    | ...
     36     |   1    | bit 4 of the green intensity (most significant bit)
            |        | is bit 1 of the pixel
     37..37 |  -1    | bits are not used
            |        |
            |        |
     48     |   8    | bit 0 of the blue intensity (least significant bit)
            |        | is bit 8 of the pixel
     49     |   9    | bit 1 of the blue intensity is bit 9 of the pixel
     50     |  10    | ...
     51     |  11    | ...
     52     |  12    | bit 4 of the green intensity (most significant bit)
            |        | is bit 12 of the pixel
     53..63 |  -1    | bits are not used
            |        |
            |        |
     64..79 |  -1    | no alpha channel
            |        |
            |        |
     80..95 |  -1    | no genlock/overlay
            |        |
            |        |
     96     |   7    | bit 7 is an unused bit
     97..127|  -1    | no further unused bits
            |        |
\endverbatim
 *
 *  @note
 *  The output in work_out[5..7/14] only exist since EdDI 1.1. Check the cookie 
 *  version before you use them.
 *
 *
 */

void
vq_scrninfo (short handle, short *work_out)
{
	short vdi_control[VDI_CNTRLMAX]; 
	static short vdi_intin[1] = {2};   

	VDI_PARAMS(vdi_control, vdi_intin, 0L, work_out, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 102,1, 0,1);
}
