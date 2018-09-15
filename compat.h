//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//Copyright (c) 2004 by Kevin Sadler								                    //
//																						//
//////////////////////////////////////////////////////////////////////////////////////////
//This file is part of Liberal Crime Squad.												//
//																						//
//    Liberal Crime Squad is free software; you can redistribute it and/or modify		//
//    it under the terms of the GNU General Public License as published by				//
//    the Free Software Foundation; either version 2 of the License, or					//
//    (at your option) any later version.												//
//																						//
//    Liberal Crime Squad is distributed in the hope that it will be useful,			//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of					//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						//
//    GNU General Public License for more details.										//
//																						//
//    You should have received a copy of the GNU General Public License					//
//    along with Liberal Crime Squad; if not, write to the Free Software				//
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA			//
//////////////////////////////////////////////////////////////////////////////////////////
 #ifndef HAS_SRTICMP
 // Portable equivalent of Windows stricmp() function.
 // This is strcmp() on lowercase versions of the
 //string.
 
 //strToLower() allocates a string and converts it to
 //Lower Case using POSIX tolower() function.
 //Free returned string after use.
 
 char *strToLower(const char *str);
 
 int stricmp(const char *str1, const char *str2);
 #endif

  #ifdef Linux // BSD and SVr4 too

  extern int init_alarm;
  extern struct itimerval timer_off;

void alarmHandler(int signal);

void setTimeval(struct  timeval *value, long sec, long usec);
void msToItimerval(int ms, struct  itimerval *value);
#endif 
  
void pause_ms(int t);
void alarmset(int t);
void alarmwait();

