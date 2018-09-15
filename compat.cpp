//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//Copyright (c) 2004 by Kevin Sadler											//
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
/* Headers for Portability */
  #include <string.h>
  #include <stdlib.h>
#ifdef WIN32
  #include <windows.h>
  #define HAS_STRICMP
#else
 #ifdef Linux // And BSD and SVr4
    #include <unistd.h>
    #include <sys/time.h>  
    #include <signal.h>
    #include <ctype.h>
  #endif 
#endif


 #ifndef HAS_STRICMP
 // Portable equivalent of Windows stricmp() function.
 // This is strcmp() on lowercase versions of the
 //string.
 
 //strToLower() allocates a string and converts it to
 //Lower Case using POSIX tolower() function.
 //Free returned string after use.
 
 char *strToLower(const char *str)
 {
 int len = strlen(str);
 char *lstr = NULL;
 int i = 0;
 
 lstr = (char *)malloc((len+1)*sizeof(char));
 
 for (i=0; i< len; i++)
 {
 lstr[i] = tolower(str[i]);
 }
 return(lstr);
 }
 
 int stricmp(const char *str1, const char *str2)
 {
 char *lstr1 = NULL;
 char *lstr2 = NULL;
 int result = 0;
  
 lstr1=strToLower(str1);
 lstr2=strToLower(str2);
   
 result = strcmp(lstr1, lstr2);
 
 free(lstr1);
 free(lstr2);
 
 return(result);
 }
 #endif
 
 
 #ifdef Linux // BSD and SVr4 too
 
  int init_alarm = 0; // Flag to indicate if alarmHandler() has been registered.
  struct itimerval timer_off;
  struct itimerval timer_on;


void alarmHandler(int signal)
{
 //WAKE UP and turn the timer off, this will un-pause().
  setitimer(ITIMER_REAL, &timer_off, NULL); 
}  

void setTimeval(struct  timeval *value, long sec, long usec)
{
  value->tv_sec = sec;
  value->tv_usec = usec;
}

void msToItimerval(int ms, struct  itimerval *value)
{
long sec=0;
long usec=0;

  if (ms > 999)
    {
     sec = (long)(ms/1000);
     usec = (long)((ms%1000)*1000);
    }
    else
    {
      usec = (long)(ms*1000);    
    }
    
 setTimeval(&value->it_interval, sec, usec);
 setTimeval(&value->it_value, sec, usec);    
}

void initalarm()
    {
     signal(SIGALRM, &alarmHandler);
     init_alarm=1;
     /* Initialise a zero value itimerval that will turn the timer off.*/
     setTimeval(&timer_off.it_interval, 0, 0);
     setTimeval(&timer_off.it_value, 0, 0);
    }
#endif 

#ifdef WIN32
  unsigned long time=GetTickCount();
#endif

void alarmset(int t)
{
#ifdef WIN32
  time=GetTickCount() + t;
#else
  /* If the signal handler is not set up set it up now */
  if (init_alarm==0)
    {
     initalarm();
    }
  // setitimer() will start a timer, pause() will stop the process until a
  // SGIALRM from the timer is recieved. This will be caught be alarmHandler()
  // which will turn off the timer and the process will resume.  
  msToItimerval(t, &timer_on);
  setitimer(ITIMER_REAL, &timer_on, NULL); 
#endif
}

void alarmwait()
{
#ifdef WIN32
 while(time > GetTickCount());
#else
  struct itimerval timer_now;
  getitimer(ITIMER_REAL, &timer_now);
  //If the timer is on we will wait for it to complete...
  if (
  ((timer_now.it_interval.tv_sec!=0)&&
   (timer_now.it_interval.tv_usec!=0))&&
  ((timer_now.it_value.tv_sec!=0)&&
   (timer_now.it_value.tv_usec!=0)))
  {
   pause();
  }
#endif
}
  
void pause_ms(int t)
{
  #ifdef Linux // BSD and SVr4 too

  alarmset(t);
  
  pause();
  
 #else
   #ifdef WIN32
  time=GetTickCount() + t;
 
 // Sadler - In 3.05 this while() was also checking that time <= GetTickCount()
 //          but as that should always be true it is removed.
 while(time > GetTickCount());
   #endif
 
 #endif
  
}

 
