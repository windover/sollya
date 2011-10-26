/*

Copyright 2011 by

Laboratoire d'Informatique de Paris 6, equipe PEQUAN,
UPMC Universite Paris 06 - CNRS - UMR 7606 - LIP6, Paris, France

Contributor Ch. Lauter

christoph.lauter@ens-lyon.org

This software is a computer program whose purpose is to provide an
environment for safe floating-point code development. It is
particularily targeted to the automatized implementation of
mathematical floating-point libraries (libm). Amongst other features,
it offers a certified infinity norm, an automatic polynomial
implementer and a fast Remez algorithm.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.

This program is distributed WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <wchar.h>
#include "expression.h"
#include "general.h"
#include "mpfi-compat.h"
#include "execute.h"
#include "printf.h"
#include "infnorm.h"
#include "execute.h"

int sollyaInternalVfprintf(FILE *fd, const char *format, va_list varlist) {
  int res = 0;
  char *buf;
  const char *currFormat;
  char *currBuf;
  int r, shiftedState, starModifiers, hModifiers;
  int lModifiers, LModifier, jModifier, zModifier;
  int tModifier;
  char c;
  int tempInt;
  ssize_t tempSsize_t;
  intmax_t tempIntmax_t;
  ptrdiff_t tempPtrdiff_t;
  long int tempLongInt;
  long long int tempLongLongInt;
  short int tempShortInt;
  signed char tempSignedChar;
  int firstStarInt, secondStarInt;
  unsigned int tempUInt;
  size_t tempSize_t;
  uintmax_t tempUintmax_t;
  unsigned long int tempULongInt;
  unsigned long long int tempULongLongInt;
  unsigned short int tempUShortInt;
  unsigned char tempUnsignedChar;
  double tempDouble;
  long double tempLongDouble;
  wint_t tempWint_t;
  char *tempCharPtr;
  wchar_t *tempWCharPtr;
  void *tempVoidPtr;
  int *tempIntPtr;
  signed char *tempSignedCharPtr;
  short int *tempShortIntPtr;
  long int *tempLongIntPtr;
  long long int *tempLongLongIntPtr;
  char *tempString;
  int isPercent;
  mpfr_t *tempMpfrPtr;
  sollya_mpfi_t *tempMpfiPtr;
  node *tempNode;

  buf = (char *) safeCalloc(strlen(format) + 1, sizeof(char));

  currBuf = buf;
  *currBuf = '\0';
  shiftedState = 0;
  currFormat = format;
  while (*currFormat != '\0') {
    switch (*currFormat) {
    case '%':
      *currBuf = *currFormat;
      currBuf++;
      *currBuf = '\0';
      currFormat++;
      shiftedState = 1;
      starModifiers = 0;
      hModifiers = 0;
      lModifiers = 0; 
      LModifier = 0; 
      jModifier = 0; 
      zModifier = 0;
      tModifier = 0;
      while ((*currFormat != '\0') && 
	     (shiftedState != 0)) {
	*currBuf = *currFormat;
	currBuf++;
	*currBuf = '\0';
	c = *currFormat;
	currFormat++;
	switch (c) {
	case '*':
	  starModifiers++;
	  break;
	case 'h':
	  hModifiers++;
	  break;
	case 'l':
	  lModifiers++;
	  break;
	case 'L':
	  LModifier = 1;
	  break;
	case 'q':
	  lModifiers += 2;
	  break;
	case 'j':
	  jModifier = 1;
	  break;
	case 'z':
	  zModifier = 1;
	  break;
	case 't':
	  tModifier = 1;
	  break;
	case 'd':
	case 'i':
	  switch (starModifiers) {
	  case 0:
	    // No star modifier given
	    //
	    // We do not have to read an extra int
	    //
	    switch (hModifiers) {
	    case 0:
	      switch (lModifiers) {
	      case 0:
		if (jModifier) {
		  // intmax_t integer conversion, no star
		  tempIntmax_t = va_arg(varlist,intmax_t);
		  r = fprintf(fd, buf, tempIntmax_t);
		  if (r >= 0) {
		    if (res >= 0) {
		      res += r;
		    } 
		  } else {
		    res = r;
		  }
		  currBuf = buf;
		  *currBuf = '\0';
		} else {
		  if (zModifier) {
		    // ssize_t integer conversion, no star
		    tempSsize_t = va_arg(varlist,ssize_t);
		    r = fprintf(fd, buf, tempSsize_t);
		    if (r >= 0) {
		      if (res >= 0) {
			res += r;
		      } 
		    } else {
		      res = r;
		    }
		    currBuf = buf;
		    *currBuf = '\0';
		  } else {
		    if (tModifier) {
		      // ptrdiff_t integer conversion, no star
		      tempPtrdiff_t = va_arg(varlist,ptrdiff_t);
		      r = fprintf(fd, buf, tempPtrdiff_t);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    } else {
		      // int integer conversion, no star
		      tempInt = va_arg(varlist,int);
		      r = fprintf(fd, buf, tempInt);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    }
		  }
		}
		break;
	      case 1:
		// long int integer conversion, no star
		tempLongInt = va_arg(varlist,long int);
		r = fprintf(fd, buf, tempLongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      default:
		// long long int integer conversion, no star
		tempLongLongInt = va_arg(varlist,long long int);
		r = fprintf(fd, buf, tempLongLongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      }
	      break;
	    case 1:
	      // short int integer conversion, no star
	      // 
	      // short int integers get promoted to 
	      // int when passed through variable args.
	      //
	      tempShortInt = (short int) (va_arg(varlist,int));
	      r = fprintf(fd, buf, tempShortInt);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    default:
	      // signed char integer conversion, no star
	      // 
	      // signed char integers get promoted to 
	      // int when passed through variable args.
	      //
	      tempSignedChar = (signed char) (va_arg(varlist,int));
	      r = fprintf(fd, buf, tempSignedChar);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    }
	    break;
	  case 1:
	    // One star modifier given
	    //
	    // We have to read an extra int
	    //	    
	    firstStarInt = va_arg(varlist,int);
	    switch (hModifiers) {
	    case 0:
	      switch (lModifiers) {
	      case 0:
		if (jModifier) {
		  // intmax_t integer conversion, one star
		  tempIntmax_t = va_arg(varlist,intmax_t);
		  r = fprintf(fd, buf, firstStarInt, tempIntmax_t);
		  if (r >= 0) {
		    if (res >= 0) {
		      res += r;
		    } 
		  } else {
		    res = r;
		  }
		  currBuf = buf;
		  *currBuf = '\0';
		} else {
		  if (zModifier) {
		    // ssize_t integer conversion, one star
		    tempSsize_t = va_arg(varlist,ssize_t);
		    r = fprintf(fd, buf, firstStarInt, tempSsize_t);
		    if (r >= 0) {
		      if (res >= 0) {
			res += r;
		      } 
		    } else {
		      res = r;
		    }
		    currBuf = buf;
		    *currBuf = '\0';
		  } else {
		    if (tModifier) {
		      // ptrdiff_t integer conversion, one star
		      tempPtrdiff_t = va_arg(varlist,ptrdiff_t);
		      r = fprintf(fd, buf, firstStarInt, tempPtrdiff_t);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    } else {
		      // int integer conversion, one star
		      tempInt = va_arg(varlist,int);
		      r = fprintf(fd, buf, firstStarInt, tempInt);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    }
		  }
		}
		break;
	      case 1:
		// long int integer conversion, one star
		tempLongInt = va_arg(varlist,long int);
		r = fprintf(fd, buf, firstStarInt, tempLongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      default:
		// long long int integer conversion, one star
		tempLongLongInt = va_arg(varlist,long long int);
		r = fprintf(fd, buf, firstStarInt, tempLongLongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      }
	      break;
	    case 1:
	      // short int integer conversion, one star
	      // 
	      // short int integers get promoted to 
	      // int when passed through variable args.
	      //
	      tempShortInt = (short int) (va_arg(varlist,int));
	      r = fprintf(fd, buf, firstStarInt, tempShortInt);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    default:
	      // signed char integer conversion, one star
	      // 
	      // signed char integers get promoted to 
	      // int when passed through variable args.
	      //
	      tempSignedChar = (signed char) (va_arg(varlist,int));
	      r = fprintf(fd, buf, firstStarInt, tempSignedChar);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    }
	    break;
	  default:
	    // Two (or more) star modifiers given
	    //
	    // We have to read two extra ints
	    //	    
	    firstStarInt = va_arg(varlist,int);
	    secondStarInt = va_arg(varlist,int);
	    switch (hModifiers) {
	    case 0:
	      switch (lModifiers) {
	      case 0:
		if (jModifier) {
		  // intmax_t integer conversion, one star
		  tempIntmax_t = va_arg(varlist,intmax_t);
		  r = fprintf(fd, buf, firstStarInt, secondStarInt, tempIntmax_t);
		  if (r >= 0) {
		    if (res >= 0) {
		      res += r;
		    } 
		  } else {
		    res = r;
		  }
		  currBuf = buf;
		  *currBuf = '\0';
		} else {
		  if (zModifier) {
		    // ssize_t integer conversion, one star
		    tempSsize_t = va_arg(varlist,ssize_t);
		    r = fprintf(fd, buf, firstStarInt, secondStarInt, tempSsize_t);
		    if (r >= 0) {
		      if (res >= 0) {
			res += r;
		      } 
		    } else {
		      res = r;
		    }
		    currBuf = buf;
		    *currBuf = '\0';
		  } else {
		    if (tModifier) {
		      // ptrdiff_t integer conversion, one star
		      tempPtrdiff_t = va_arg(varlist,ptrdiff_t);
		      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempPtrdiff_t);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    } else {
		      // int integer conversion, one star
		      tempInt = va_arg(varlist,int);
		      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempInt);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    }
		  }
		}
		break;
	      case 1:
		// long int integer conversion, one star
		tempLongInt = va_arg(varlist,long int);
		r = fprintf(fd, buf, firstStarInt, secondStarInt, tempLongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      default:
		// long long int integer conversion, one star
		tempLongLongInt = va_arg(varlist,long long int);
		r = fprintf(fd, buf, firstStarInt, secondStarInt, tempLongLongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      }
	      break;
	    case 1:
	      // short int integer conversion, one star
	      // 
	      // short int integers get promoted to 
	      // int when passed through variable args.
	      //
	      tempShortInt = (short int) (va_arg(varlist,int));
	      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempShortInt);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    default:
	      // signed char integer conversion, one star
	      // 
	      // signed char integers get promoted to 
	      // int when passed through variable args.
	      //
	      tempSignedChar = (signed char) (va_arg(varlist,int));
	      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempSignedChar);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    }
	    break;
	  }
	  shiftedState = 0;
	  break;
	case 'o':
	case 'u':
	case 'x':
	case 'X':
	  switch (starModifiers) {
	  case 0:
	    // No star modifier given
	    //
	    // We do not have to read an extra int
	    //
	    switch (hModifiers) {
	    case 0:
	      switch (lModifiers) {
	      case 0:
		if (jModifier) {
		  // uintmax_t integer conversion, no star
		  tempUintmax_t = va_arg(varlist,uintmax_t);
		  r = fprintf(fd, buf, tempUintmax_t);
		  if (r >= 0) {
		    if (res >= 0) {
		      res += r;
		    } 
		  } else {
		    res = r;
		  }
		  currBuf = buf;
		  *currBuf = '\0';
		} else {
		  if (zModifier) {
		    // size_t integer conversion, no star
		    tempSize_t = va_arg(varlist,size_t);
		    r = fprintf(fd, buf, tempSize_t);
		    if (r >= 0) {
		      if (res >= 0) {
			res += r;
		      } 
		    } else {
		      res = r;
		    }
		    currBuf = buf;
		    *currBuf = '\0';
		  } else {
		    if (tModifier) {
		      // ptrdiff_t integer conversion, no star
		      tempPtrdiff_t = va_arg(varlist,ptrdiff_t);
		      r = fprintf(fd, buf, tempPtrdiff_t);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    } else {
		      // unsigned int integer conversion, no star
		      tempUInt = va_arg(varlist,unsigned int);
		      r = fprintf(fd, buf, tempUInt);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    }
		  }
		}
		break;
	      case 1:
		// unsigned long int integer conversion, no star
		tempULongInt = va_arg(varlist,unsigned long int);
		r = fprintf(fd, buf, tempULongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      default:
		// unsigned long long int integer conversion, no star
		tempULongLongInt = va_arg(varlist,unsigned long long int);
		r = fprintf(fd, buf, tempULongLongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      }
	      break;
	    case 1:
	      // unsigned short int integer conversion, no star
	      // 
	      // unsigned short int integers get promoted to 
	      // unsigned int when passed through variable args.
	      //
	      tempUShortInt = (unsigned short int) (va_arg(varlist,unsigned int));
	      r = fprintf(fd, buf, tempUShortInt);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    default:
	      // unsigned char integer conversion, no star
	      // 
	      // unsigned char integers get promoted to 
	      // unsigned int when passed through variable args.
	      //
	      tempUnsignedChar = (unsigned char) (va_arg(varlist,unsigned int));
	      r = fprintf(fd, buf, tempUnsignedChar);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    }
	    break;
	  case 1:
	    // One star modifier given
	    //
	    // We have to read an extra int
	    //	    
	    firstStarInt = va_arg(varlist,int);
	    switch (hModifiers) {
	    case 0:
	      switch (lModifiers) {
	      case 0:
		if (jModifier) {
		  // uintmax_t integer conversion, one star
		  tempUintmax_t = va_arg(varlist,uintmax_t);
		  r = fprintf(fd, buf, firstStarInt, tempUintmax_t);
		  if (r >= 0) {
		    if (res >= 0) {
		      res += r;
		    } 
		  } else {
		    res = r;
		  }
		  currBuf = buf;
		  *currBuf = '\0';
		} else {
		  if (zModifier) {
		    // size_t integer conversion, one star
		    tempSize_t = va_arg(varlist,size_t);
		    r = fprintf(fd, buf, firstStarInt, tempSize_t);
		    if (r >= 0) {
		      if (res >= 0) {
			res += r;
		      } 
		    } else {
		      res = r;
		    }
		    currBuf = buf;
		    *currBuf = '\0';
		  } else {
		    if (tModifier) {
		      // ptrdiff_t integer conversion, one star
		      tempPtrdiff_t = va_arg(varlist,ptrdiff_t);
		      r = fprintf(fd, buf, firstStarInt, tempPtrdiff_t);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    } else {
		      // unsigned int integer conversion, one star
		      tempUInt = va_arg(varlist,unsigned int);
		      r = fprintf(fd, buf, firstStarInt, tempUInt);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    }
		  }
		}
		break;
	      case 1:
		// unsigned long int integer conversion, one star
		tempULongInt = va_arg(varlist,unsigned long int);
		r = fprintf(fd, buf, firstStarInt, tempULongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      default:
		// unsigned long long int integer conversion, one star
		tempULongLongInt = va_arg(varlist,unsigned long long int);
		r = fprintf(fd, buf, firstStarInt, tempULongLongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      }
	      break;
	    case 1:
	      // unsigned short int integer conversion, one star
	      // 
	      // unsigned short int integers get promoted to 
	      // unsigned int when passed through variable args.
	      //
	      tempUShortInt = (unsigned short int) (va_arg(varlist,unsigned int));
	      r = fprintf(fd, buf, firstStarInt, tempUShortInt);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    default:
	      // unsigned char integer conversion, one star
	      // 
	      // unsigned char integers get promoted to 
	      // unsigned int when passed through variable args.
	      //
	      tempUnsignedChar = (unsigned char) (va_arg(varlist,unsigned int));
	      r = fprintf(fd, buf, firstStarInt, tempUnsignedChar);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    }
	    break;
	  default:
	    // Two (or more) star modifiers given
	    //
	    // We have to read two extra ints
	    //	    
	    firstStarInt = va_arg(varlist,int);
	    secondStarInt = va_arg(varlist,int);
	    switch (hModifiers) {
	    case 0:
	      switch (lModifiers) {
	      case 0:
		if (jModifier) {
		  // uintmax_t integer conversion, one star
		  tempUintmax_t = va_arg(varlist,uintmax_t);
		  r = fprintf(fd, buf, firstStarInt, secondStarInt, tempUintmax_t);
		  if (r >= 0) {
		    if (res >= 0) {
		      res += r;
		    } 
		  } else {
		    res = r;
		  }
		  currBuf = buf;
		  *currBuf = '\0';
		} else {
		  if (zModifier) {
		    // size_t integer conversion, one star
		    tempSize_t = va_arg(varlist,size_t);
		    r = fprintf(fd, buf, firstStarInt, secondStarInt, tempSize_t);
		    if (r >= 0) {
		      if (res >= 0) {
			res += r;
		      } 
		    } else {
		      res = r;
		    }
		    currBuf = buf;
		    *currBuf = '\0';
		  } else {
		    if (tModifier) {
		      // ptrdiff_t integer conversion, one star
		      tempPtrdiff_t = va_arg(varlist,ptrdiff_t);
		      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempPtrdiff_t);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    } else {
		      // unsigned int integer conversion, one star
		      tempUInt = va_arg(varlist,unsigned int);
		      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempUInt);
		      if (r >= 0) {
			if (res >= 0) {
			  res += r;
			} 
		      } else {
			res = r;
		      }
		      currBuf = buf;
		      *currBuf = '\0';
		    }
		  }
		}
		break;
	      case 1:
		// unsigned long int integer conversion, one star
		tempULongInt = va_arg(varlist,unsigned long int);
		r = fprintf(fd, buf, firstStarInt, secondStarInt, tempULongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      default:
		// unsigned long long int integer conversion, one star
		tempULongLongInt = va_arg(varlist,unsigned long long int);
		r = fprintf(fd, buf, firstStarInt, secondStarInt, tempULongLongInt);
		if (r >= 0) {
		  if (res >= 0) {
		    res += r;
		  } 
		} else {
		  res = r;
		}
		currBuf = buf;
		*currBuf = '\0';
		break;
	      }
	      break;
	    case 1:
	      // unsigned short int integer conversion, one star
	      // 
	      // unsigned short int integers get promoted to 
	      // unsigned int when passed through variable args.
	      //
	      tempUShortInt = (unsigned short int) (va_arg(varlist,unsigned int));
	      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempUShortInt);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    default:
	      // unsigned char integer conversion, one star
	      // 
	      // unsigned char integers get promoted to 
	      // unsigned int when passed through variable args.
	      //
	      tempUnsignedChar = (unsigned char) (va_arg(varlist,unsigned int));
	      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempUnsignedChar);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    }
	    break;
	  }
	  shiftedState = 0;
	  break;
	case 'e':
	case 'E':
	case 'f':
	case 'F':
	case 'g':
	case 'G':
	case 'a':
	case 'A':
	  switch (starModifiers) {
	  case 0:
	    // No star modifier given
	    //
	    // We do not have to read an extra int
	    //
	    if (LModifier) {
	      // The floating-point conversion takes
	      // a long double argument
	      //
	      tempLongDouble = va_arg(varlist,long double);
	      r = fprintf(fd, buf, tempLongDouble);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    } else {
	      // The floating-point conversion takes
	      // a double argument
	      //
	      tempDouble = va_arg(varlist,double);
	      r = fprintf(fd, buf, tempDouble);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    }
	    break;
	  case 1:
	    // One star modifier given
	    //
	    // We have to read one extra int
	    //
	    firstStarInt = va_arg(varlist,int);
	    if (LModifier) {
	      // The floating-point conversion takes
	      // a long double argument
	      //
	      tempLongDouble = va_arg(varlist,long double);
	      r = fprintf(fd, buf, firstStarInt, tempLongDouble);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    } else {
	      // The floating-point conversion takes
	      // a double argument
	      //
	      tempDouble = va_arg(varlist,double);
	      r = fprintf(fd, buf, firstStarInt, tempDouble);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    }
	    break;
	  default:
	    // Two (or more) star modifiers given
	    //
	    // We have to read two extra ints
	    //
	    firstStarInt = va_arg(varlist,int);
	    secondStarInt = va_arg(varlist,int);
	    if (LModifier) {
	      // The floating-point conversion takes
	      // a long double argument
	      //
	      tempLongDouble = va_arg(varlist,long double);
	      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempLongDouble);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    } else {
	      // The floating-point conversion takes
	      // a double argument
	      //
	      tempDouble = va_arg(varlist,double);
	      r = fprintf(fd, buf, firstStarInt, secondStarInt, tempDouble);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    }
	    break;
	  }
	  shiftedState = 0;
	  break;
	case 'C':
	  lModifiers++;
	  // Fall-through...
	case 'c':
	  if (lModifiers == 0) {
	    tempUnsignedChar = (unsigned char) va_arg(varlist,int);
	    r = fprintf(fd, buf, tempUnsignedChar);
	    if (r >= 0) {
	      if (res >= 0) {
		res += r;
	      } 
	    } else {
	      res = r;
	    }
	    currBuf = buf;
	    *currBuf = '\0';
	  } else {
	    tempWint_t = va_arg(varlist,wint_t);
	    r = fprintf(fd, buf, tempWint_t);
	    if (r >= 0) {
	      if (res >= 0) {
		res += r;
	      } 
	    } else {
	      res = r;
	    }
	    currBuf = buf;
	    *currBuf = '\0';
	  }
	  shiftedState = 0;
	  break;
	case 'S':
	  lModifiers++;
	  // Fall-through...
	case 's':
	  if (starModifiers == 0) {
	    // No star modifier given
	    //
	    // We do not have to read an extra int
	    //
	    if (lModifiers == 0) {
	      tempCharPtr = va_arg(varlist,char *);
	      r = fprintf(fd, buf, tempCharPtr);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    } else {
	      tempWCharPtr = va_arg(varlist,wchar_t *);
	      r = fprintf(fd, buf, tempWCharPtr);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    }
	  } else {
	    // One star modifier given
	    //
	    // We have to read one extra int
	    //
	    firstStarInt = va_arg(varlist,int);
	    if (lModifiers == 0) {
	      tempCharPtr = va_arg(varlist,char *);
	      r = fprintf(fd, buf, firstStarInt, tempCharPtr);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    } else {
	      tempWCharPtr = va_arg(varlist,wchar_t *);
	      r = fprintf(fd, buf, firstStarInt, tempWCharPtr);
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	    }
	  }
	  shiftedState = 0;
	  break;
	case 'p':
	  tempVoidPtr = va_arg(varlist,void *);
	  r = fprintf(fd, buf, tempVoidPtr);
	  if (r >= 0) {
	    if (res >= 0) {
	      res += r;
	    } 
	  } else {
	    res = r;
	  }
	  currBuf = buf;
	  *currBuf = '\0';
	  shiftedState = 0;
	  break;
	case 'n':
	  switch (hModifiers) {
	  case 0:
	    switch (lModifiers) {
	    case 0:
	      // int * argument
	      //
	      tempIntPtr = va_arg(varlist,int *);
	      r = fprintf(fd, buf, &tempInt);
	      if (res >= 0) {
		*tempIntPtr = tempInt + res;
	      } else {
		*tempIntPtr = 0;
	      }
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    case 1:
	      // long int * argument
	      //
	      tempLongIntPtr = va_arg(varlist,long int *);
	      r = fprintf(fd, buf, &tempLongInt);
	      if (res >= 0) {
		*tempLongIntPtr = tempLongInt + res;
	      } else {
		*tempLongIntPtr = 0;
	      }
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    default:
	      // long long int * argument
	      //
	      tempLongLongIntPtr = va_arg(varlist,long long int *);
	      r = fprintf(fd, buf, &tempLongLongInt);
	      if (res >= 0) {
		*tempLongLongIntPtr = tempLongLongInt + res;
	      } else {
		*tempLongLongIntPtr = 0;
	      }
	      if (r >= 0) {
		if (res >= 0) {
		  res += r;
		} 
	      } else {
		res = r;
	      }
	      currBuf = buf;
	      *currBuf = '\0';
	      break;
	    }
	    break;
	  case 1:
	    // short int * argument
	    //
	    tempShortIntPtr = va_arg(varlist,short int *);
	    r = fprintf(fd, buf, &tempShortInt);
	    if (res >= 0) {
	      *tempShortIntPtr = tempShortInt + res;
	    } else {
	      *tempShortIntPtr = 0;
	    }
	    if (r >= 0) {
	      if (res >= 0) {
		res += r;
	      } 
	    } else {
	      res = r;
	    }
	    currBuf = buf;
	    *currBuf = '\0';	    
	    break;
	  default:
	    // signed char * argument
	    //
	    tempSignedCharPtr = va_arg(varlist,signed char *);
	    r = fprintf(fd, buf, &tempSignedChar);
	    if (res >= 0) {
	      *tempSignedCharPtr = tempSignedChar + res;
	    } else {
	      *tempSignedCharPtr = 0;
	    }
	    if (r >= 0) {
	      if (res >= 0) {
		res += r;
	      } 
	    } else {
	      res = r;
	    }
	    currBuf = buf;
	    *currBuf = '\0';	    
	    break;
	  }
	  shiftedState = 0;
	  break;
	case 'm':
	case '%':
	  r = fprintf(fd, buf);
	  if (r >= 0) {
	    if (res >= 0) {
	      res += r;
	    } 
	  } else {
	    res = r;
	  }
	  currBuf = buf;
	  *currBuf = '\0';
	  shiftedState = 0;
	  break;
	case 'v':
	case 'w':
	case 'b':
	  /* Still free, too: k, r, y */
	  while (currBuf > buf) {
	    currBuf--;
	    isPercent = (*currBuf == '%');
	    *currBuf = '\0';
	    if (isPercent) break;
	  }
	  *currBuf = '%';
	  currBuf++;
	  *currBuf = 's';
	  currBuf++;
	  *currBuf = '\0';
	  switch (c) {
	  case 'v':
	    tempMpfrPtr = va_arg(varlist,mpfr_t *);
	    if (tempMpfrPtr != NULL) {
	      tempString = sprintValue(tempMpfrPtr);
	    } else {
	      tempString = safeCalloc(5,sizeof(char));
	      sprintf(tempString,"NULL");
	    }
	    break;
	  case 'w':
	    tempMpfiPtr = va_arg(varlist,sollya_mpfi_t *);
	    if (tempMpfiPtr != NULL) {
	      tempString = sprintInterval(*tempMpfiPtr);
	    } else {
	      tempString = safeCalloc(5,sizeof(char));
	      sprintf(tempString,"NULL");
	    }
	    break;
	  case 'b':
	    tempNode = va_arg(varlist,node *);
	    if (tempNode != NULL) {
	      tempString = sPrintThing(tempNode);
	    } else {
	      tempString = safeCalloc(5,sizeof(char));
	      sprintf(tempString,"NULL");
	    }
	    break;
	  default:
	    tempString = (char *) safeCalloc(1,sizeof(char));
	    break;
	  }
	  r = fprintf(fd, buf, tempString);
	  if (r >= 0) {
	    if (res >= 0) {
	      res += r;
	    } 
	  } else {
	    res = r;
	  }
	  currBuf = buf;
	  *currBuf = '\0';
	  free(tempString);
	  shiftedState = 0;
	  break;
	default:
	  break;
	}
      }
      break;
    default:
      *currBuf = *currFormat;
      currBuf++;
      *currBuf = '\0';
      currFormat++;
      break;
    }
  }
  if (currBuf != buf) {
    r = fprintf(fd, buf);
    if (r >= 0) {
      if (res >= 0) {
	res += r;
      } 
    } else {
      res = r;
    }
  }

  free(buf);
  return res;
}

