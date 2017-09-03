#ifndef Singleton_H
#define Singleton_H

template<typename T>
class Singleton {
  public:
    static T& Get () {
      static T singletonInstance;
      return singletonInstance;
    }
  private:
    // Singleton ();
    // Singleton (Singleton const&); // Don't Implement
    void operator= (Singleton const&); // Don't implement
};

#endif
