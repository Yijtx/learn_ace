#include <ace/OS.h>
#include <ace/Message_Block.h>


#ifdef _DEBUG    

#pragma comment(lib, "ACEd.lib")

#else

#pragma comment(lib, "ACE.lib")

#endif

ACE_INT32 ACE_TMAIN(ACE_INT32 argc, ACE_TCHAR* argv[])
{

	ACE_Message_Block *head = new ACE_Message_Block(BUFSIZ);

	ACE_Message_Block *mblk = head;

	for (;;){
		ssize_t nbytes = ACE_OS::read_n(ACE_STDIN,
			mblk->wr_ptr(),
			mblk->size());
		if (nbytes <= 0)
			break;
		mblk->wr_ptr(nbytes);
		mblk->cont(new ACE_Message_Block(BUFSIZ));
		mblk = mblk->cont();
		//print
		for (mblk = head; mblk != 0; mblk = mblk->cont())
			ACE_OS::write_n(ACE_STDOUT, mblk->rd_ptr(), mblk->length());
		head->release();
		return 0;
	}
	return 0;
}
