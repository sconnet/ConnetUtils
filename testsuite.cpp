/*

  g++ -Wall -o server_test server_test.cpp -I/usr/devel/ConnetUtils/include -L/usr/devel/ConnetUtils/lib -lConnetUtils
 */

#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "Thread.h"

using namespace std;
//using namespace ConnetUtils;

class ThreadedObject : public Thread
{
public:
  ThreadedObject() {}
  void run()
  {
    for( int x = 0; x < 10; ++x )
    {
      cout << x << "/10: hello from the thread" << endl;
      if( waitForKillEvent( 1000 ) )
        break;
    }
  }
};

bool read_client(int fd, void* data = 0)
{
  data = 0;
  const int buf_size = 8192; // 8k
  char buf[buf_size + 1];

  memset (buf, 0, buf_size);
  int bytes = read (fd, (char*)buf, buf_size);
  if (bytes <= 0)
    return false;

  // write this to a file
  cout << buf << endl;

  return true;
}

int main()
{
  ThreadedObject thread;
  thread.start();
  Server server;

  try
  {
    server.listen(32000, read_client);
    server.select();
  }
  catch(const Exception& ex)
  {
    cout << ex << endl;
  }

  thread.stop();
}
