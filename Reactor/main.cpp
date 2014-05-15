// Ch2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <ace/Log_Msg.h>
#include "acceptor.h"
#include "handle_data.h"

#ifdef _DEBUG    

#pragma comment(lib, "ACEd.lib")

#else

#pragma comment(lib, "ACE.lib")

#endif

ACE_INT32 ACE_TMAIN(ACE_INT32 argc, ACE_TCHAR* argv[])
{

	ACE_UINT16  port = 0;
	if (argc < 2)
		return -1;
	port = ACE_OS::atoi(argv[1]);
	Acceptor    *accept;

	ACE_NEW_RETURN(accept, Acceptor(ACE_Reactor::instance()), -1);
	if (accept->open(port) == -1)
	{
		accept->handle_close();
		ACE_DEBUG((LM_DEBUG, "main open error!\n"));
		return -1;
	}
	if (ACE_Reactor::run_event_loop() == -1)
	{
		accept->handle_close();
		ACE_DEBUG((LM_DEBUG, "main run event loop error!\n"));
		return -1;
	}
	accept->handle_close();
	ACE_DEBUG((LM_DEBUG,"main return!"));
	return 0;
}

