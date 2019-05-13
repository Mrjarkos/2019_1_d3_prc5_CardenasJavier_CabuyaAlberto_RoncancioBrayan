class MyThreadClass
{
public:
   MyThreadClass() {/* empty */}
   virtual ~MyThreadClass() {/* empty */}

   bool Init()
   {
      return (pthread_create(&_thread, NULL, &ThreadEntryFunc, this) == 0);
   }

   /** Will not return until the internal thread has exited. */
   void WaitForThreadToExit()
   {
      (void) pthread_join(_thread, NULL);
   }

private:
   //our friend function that runs the thread task
   friend void* ThreadEntryFunc(void *);

   pthread_t _thread;
};

//friend is defined outside of class and without any qualifiers
void* ThreadEntryFunc(void *obj_param) {
MyThreadClass *thr  = ((MyThreadClass *)obj_param);

//access all the members using thr->

return NULL;
}
