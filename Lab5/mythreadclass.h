#ifndef MYTHREADCLASS_H
#define MYTHREADCLASS_H


class MyThreadClass
{
public:
    MyThreadClass();
    virtual ~MyThreadClass() {/* empty */}

         bool Init();

         void WaitForThreadToExit();

      private:

         friend void* ThreadEntryFunc(void *);

         pthread_t _thread;
};

#endif // MYTHREADCLASS_H
