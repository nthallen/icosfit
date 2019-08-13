/* Copyright 2018, The Regents of the University of Colorado */

/* This file is part of the Eli Module Library.

The Eli Module Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Eli Module Library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the Eli Module Library; see the file COPYING.LIB.
If not, write to the Free Software Foundation, Inc., 59 Temple Place -
Suite 330, Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Eli into the
   directory resulting from a :source derivation, you may use that
   created file as a part of that directory without restriction. */

#include "coord.h"

#ifdef MONITOR
#include "dapto_dapto.h"
#include "err_dapto.h"
#endif

	/* Variables exported by the Coordinate Module */

int LineNum = 1;		/* Index of the current line
				   in the total source text */

POSITION NoCoord = { 0 };       /* The NULL coordinate */

POSITION curpos;		/* Position variable for general use */

	/* Routines exported by the Coordinate Module */

int
#ifdef PROTO_OK
earlier(CoordPtr p, CoordPtr q)
#else
earlier(p,q) CoordPtr p, q;
#endif
/* Check relative position
 *    On exit-
 *       earlier != 0 if p defines a position in the source text that
 *          preceeds the position defined by q
 ***/
{ if (p == NoPosition || q == NoPosition) return 0;
#ifdef RIGHTCOORD
  if (p->rline > q->line) return 0;
  if (p->rline < q->line) return 1;

  if (p->rcol > q->col) return 0;
  if (p->rcol < q->col) return 1;

  return (p->line != p->rline) || (p->col != p->rcol);
#else
  if (p->line != q->line) return(p->line < q->line);
  return(p->col < q->col);
#endif
}
