// BaseNode.h

#ifndef _BASENODE_h
#define _BASENODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
/*class Type
{
    public:
        virtual ~Type(){}
        virtual void* allocate()const=0;
        virtual void* cast(void* obj)const=0;
};

template<typename T> class TypeImpl : public Type
{
      public:
         virtual void* allocate()const{ return new T; }
         virtual void* cast(void* obj)const{ return static_cast<T*>(obj); }
};
*/
/*
// ...
Type* type = new TypeImpl<int>;
void* myint = type->allocate();
// ...
*/
class BaseNodeClass
{
	
protected:
	BaseNodeClass *_Owner = NULL;
	BaseNodeClass *_Inner = NULL;
	BaseNodeClass *_Prev = NULL;
	BaseNodeClass *_Next = NULL;
public:
	//bool taiming = false;
	bool autoinner = false;
	bool exit = false;
	bool _refersh = true;
	byte type = 0;
	byte type1 = 0;
	virtual ~BaseNodeClass() {};
	virtual bool allowInner();
	virtual bool allowOwner();
	virtual bool allowNext();
	virtual bool allowPrev();

	virtual BaseNodeClass *getPrev();
	virtual BaseNodeClass *getNext();
	virtual BaseNodeClass *getOwner();
	virtual BaseNodeClass *getInner();

	virtual void setPrev(BaseNodeClass *node);
	virtual void setNext(BaseNodeClass *node);
	virtual void setOwner(BaseNodeClass *node);
	virtual void setInner(BaseNodeClass *node);

	virtual void show() {};
	virtual void refresh() {};	
	void renew() {
		_refersh = false;
		show();
		_refersh = true;
	};
};



#endif

