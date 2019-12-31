# 多线程操作类

该线程类是由 MFC 的 CreateThread 创建的。

ThreadBase.h 中的 CThreadBase 类是线程的基类，定义新线程类时需要继承 CThreadBase 类。

Old CThreadBase 文件夹中的线程基类，一旦 stop 之后，将不能再次执行。

新 CThreadBase 类，修正了这一不足，并且提供 close 方法（即执行 ExitThread）来退出线程

如果线程所作工作仅仅执行一次，那么 Old CThreadBase 类也会完成得很好。

提供 CEventThread 类，当线程结束时可以抛出事件来通知相关的其他线程。

TaskThreadLib 是任务线程模型的实现。

## 任务线程模型

这个模型是为了把线程本身和线程要执行的代码（命令、任务等）分离。即这里的线程不再提供threadRun虚函数，而是提供一个类，该类被称为任务，提供一个doTask方法，在doTask方法中具体实现要执行的代码。

这样分离的好处就是，线程本身可以不变，仅替换线程中的任务类，即可实现同一个线程执行不同的任务的目标。这样的线程可以放到线程池中，需要执行的时候，传入一个任务类对象，即可开始执行任务，非常方便。

实现方式，依然继承CThreadBase，但是把threadRun定义为private，即子类不能修改该方法了，threadRun方法执行Task任务类的doTask方法。
