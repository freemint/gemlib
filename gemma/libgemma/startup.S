| Startup code for thread_fork()

|  This program is free software; you can redistribute it and/or modify
|  it under the terms of the GNU General Public License as published by
|  the Free Software Foundation; either version 2 of the License, or
|  (at your option) any later version.
|
|  This program is distributed in the hope that it will be useful,
|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|  GNU General Public License for more details.
|
|  You should have received a copy of the GNU General Public License
|  along with this program; if not, write to the Free Software
|  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

	.globl	__startup

__startup:
	move.l	0x04(sp),a2
	move.l	0x0010(a2),a3
	move.l	0x0024(a2),a0
	lea	0x0008(a0),a0
	lea	0x0008(a2),a1
	moveq	#0x05,d0
cp:
	move.l	(a0)+,(a1)+
	dbra.w	d0,cp

	move.l	0x04(sp),-(sp)
	move.w	#0x0001,-(sp)
	jsr	(a3)
	addq.l	#0x06,sp

	move.w	d0,-(sp)
	move.w	#0x004c,-(sp)
	trap	#1

| EOF
