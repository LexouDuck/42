/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2018/07/16 20:26:16 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MLX_EVENTS_H
# define __MLX_EVENTS_H

/*
**	=== INPUT EVENTS - APPLE ===
*/
# define MOUSE_L_CLICK		1
# define MOUSE_M_CLICK		3
# define MOUSE_R_CLICK		2
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define KEY_ESC			0x35

# define KEY_LEFT			0x7B
# define KEY_RIGHT			0x7C
# define KEY_DOWN			0x7D
# define KEY_UP				0x7E

# define KEY_PAGE_UP		0x74
# define KEY_PAGE_DN		0x79
# define KEY_HOME			0x73
# define KEY_END			0x77
# define KEY_HELP			0x72
# define KEY_DELETE			0x75

# define KEY_NUMPAD_0		0x52
# define KEY_NUMPAD_1		0x53
# define KEY_NUMPAD_2		0x54
# define KEY_NUMPAD_3		0x55
# define KEY_NUMPAD_4		0x56
# define KEY_NUMPAD_5		0x57
# define KEY_NUMPAD_6		0x58
# define KEY_NUMPAD_7		0x59
# define KEY_NUMPAD_8		0x5B
# define KEY_NUMPAD_9		0x5C
# define KEY_NUMPAD_PERIOD	0x41
# define KEY_NUMPAD_ENTER	0x4C
# define KEY_NUMPAD_ADD		0x45
# define KEY_NUMPAD_SUB		0x4E
# define KEY_NUMPAD_MUL		0x43
# define KEY_NUMPAD_DIV		0x4B
# define KEY_NUMPAD_CLEAR	0x47
# define KEY_NUMPAD_EQUALS	0x51

/*
**	=== EVENT DEFINES ===
*/
# define EVENT_KEYPRESS				2
# define EVENT_KEYRELEASE			3
# define EVENT_BUTTONPRESS			4
# define EVENT_BUTTONRELEASE		5
# define EVENT_MOTIONNOTIFY			6
# define EVENT_ENTERNOTIFY			7
# define EVENT_LEAVENOTIFY			8
# define EVENT_FOCUSIN				9
# define EVENT_FOCUSOUT				10
# define EVENT_KEYMAPNOTIFY			11
# define EVENT_EXPOSE				12
# define EVENT_GRAPHICSEXPOSE		13
# define EVENT_NOEXPOSE				14
# define EVENT_VISIBILITYNOTIFY		15
# define EVENT_CREATENOTIFY			16
# define EVENT_DESTROYNOTIFY		17
# define EVENT_UNMAPNOTIFY			18
# define EVENT_MAPNOTIFY			19
# define EVENT_MAPREQUEST			20
# define EVENT_REPARENTNOTIFY		21
# define EVENT_CONFIGURENOTIFY		22
# define EVENT_CONFIGUREREQUEST		23
# define EVENT_GRAVITYNOTIFY		24
# define EVENT_RESIZEREQUEST		25
# define EVENT_CIRCULATENOTIFY		26
# define EVENT_CIRCULATEREQUEST		27
# define EVENT_PROPERTYNOTIFY		28
# define EVENT_SELECTIONCLEAR		29
# define EVENT_SELECTIONREQUEST		30
# define EVENT_SELECTIONNOTIFY		31
# define EVENT_COLORMAPNOTIFY		32
# define EVENT_CLIENTMESSAGE		33
# define EVENT_MAPPINGNOTIFY		34
# define EVENT_GENERICEVENT			35
# define EVENT_LASTEVENT			36

/*
**	=== EVENT MASK DEFINES ===
**	These are the different X event bit-masks for the X-Server.
**	These are not to be confused with event names.
*/
# define MASK_NOEVENT				0L
# define MASK_KEYPRESS				(1L<<0)
# define MASK_KEYRELEASE			(1L<<1)
# define MASK_BUTTONPRESS			(1L<<2)
# define MASK_BUTTONRELEASE			(1L<<3)
# define MASK_ENTERWINDOW			(1L<<4)
# define MASK_LEAVEWINDOW			(1L<<5)
# define MASK_POINTERMOTION			(1L<<6)
# define MASK_POINTERMOTIONHINT		(1L<<7)
# define MASK_BUTTON1MOTION			(1L<<8)
# define MASK_BUTTON2MOTION			(1L<<9)
# define MASK_BUTTON3MOTION			(1L<<10)
# define MASK_BUTTON4MOTION			(1L<<11)
# define MASK_BUTTON5MOTION			(1L<<12)
# define MASK_BUTTONMOTION			(1L<<13)
# define MASK_KEYMAPSTATE			(1L<<14)
# define MASK_EXPOSURE				(1L<<15)
# define MASK_VISIBILITYCHANGE		(1L<<16)
# define MASK_STRUCTURENOTIFY		(1L<<17)
# define MASK_RESIZEREDIRECT		(1L<<18)
# define MASK_SUBSTRUCTURENOTIFY	(1L<<19)
# define MASK_SUBSTRUCTUREREDIRECT	(1L<<20)
# define MASK_FOCUSCHANGE			(1L<<21)
# define MASK_PROPERTYCHANGE		(1L<<22)
# define MASK_COLORMAPCHANGE		(1L<<23)
# define MASK_OWNERGRABBUTTON		(1L<<24)

#endif
