
/*  bullet_utilities.h                                                   */



#ifndef BULLET_UTILITIES_H
#define BULLET_UTILITIES_H

/**
	@author AndreaCatania
*/

#define bulletnew(cl) \
	new cl

#define bulletdelete(cl) \
	{                    \
		delete cl;       \
		cl = nullptr;    \
	}
#endif
