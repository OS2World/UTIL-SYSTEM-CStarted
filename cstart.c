#define INCL_DOSFILEMGR
#define INCL_DOSMISC
#include <os2.h>
#include <time.h>
#include <sys/video.h>

 
ULONG getdata(ULONG whichone)
{
	ULONG temp;
	DosQuerySysInfo ( whichone,  whichone,  &temp,  4);
	return temp;
}
void main(void)
{
	struct tm *tim;
	ULONG currtime,difftime,uptime;
	v_init();
	currtime=getdata(QSV_TIME_LOW);
	uptime=getdata(QSV_MS_COUNT);
	difftime=currtime-uptime/1000;
	tim=localtime(&difftime);
	v_attrib(0x3);
	v_printf("This computer started at (about): ");
	v_attrib(0xB);
	v_printf("%02u-%02u-%02u  %02u:%02u:%02u\n",tim->tm_year,tim->tm_mon+1,tim->tm_mday,tim->tm_hour,tim->tm_min,tim->tm_sec);
	v_attrib(0x3);
	v_printf("Current uptime: ");
	v_attrib(0xB);
	v_printf("%lud %luh %lum %lus %lums\n",(uptime/(1000*3600*24))%365,(uptime/(1000*3600))%24,(uptime/(1000*60))%60,(uptime/(1000))%60,uptime%1000);
}