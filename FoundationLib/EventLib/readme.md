# 事件处理类库

事件处理是类对象交互比较常见的操作，使用频率比较高。

## 1、同步的事件处理

代码使用上类似 C# 的 delegate，代码的实现上类似 MFC 添加的事件处理代码。支持单一对象抛出事件，也支持一个对象列表中的某个对象抛出事件。

举个简单的例子（单一对象抛出事件）：

1、使类 A 能够抛出事件

``` java
  class A : public IEventRaisable
  {
  public:
    CDelegate DoAnEvent;   // 类 A 的 DoAnEvent 事件
  
    void raise_event()
    {
      IEvent e(&a, "DoAnEvent");
      DoAnEvent.raiseEvent(&a, &e);
    };
  }
```

2、使类 B 能够处理事件

B.h

```java
class B : public IEventHandler
{
public:
  B(A *a){m_a=a;};
  Declare_Event_Map()
  
  void OnADoAnEvent(IEvent *e);
  
private:
  A *m_a;
}
```

B.cpp

```java
Begin_Event_Map(B)
Event_Map(m_a, "DoAnEvent", OnADoAnEvent);
End_Event_Map()

void B::OnADoAnEvent(IEvent *e)
{
  printf("a raised an event.");
}
```

3、main.c

```java
A a;
B b(&a);
a.DoAnEvent += &b;
a.raise_event();
```

看看是不是在屏幕上打印出了“a raised an event.”

## 2、异步的事件处理

目前考虑有两种实现方式，一种是while循环，另一种是使用线程。

对于第一种，应该是微软界面库实现的方式。但是这种方式会阻塞界面，除非对界面中的任何操作都做了事件处理，否则这种方式可能会使界面的其他操作变成无响应，也阻塞了微软界面的事件处理。

对于第二种，不会使界面阻塞，但是增加了线程数，如果每个界面控件都是用这种方式，进程中的线程数增加量很大，不知道是不是会影响性能。

但是为了不影响微软界面的事件处理，只能使用第二种方式。

提供一个异步事件处理线程类 CEventAsynHandlerThread，在该类的执行函数中，用while的方式读取异步事件。

CEventAsynHandlerThread 类使用了多线程模式中的生产消费模式类 CProductorConsumerPattern。
