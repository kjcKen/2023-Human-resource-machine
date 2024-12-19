## Human Resource Machine 实验报告

#### 一、设计思路

**1.需求分析：**

程序需要实现一个游戏的功能。要求存储输入的积木序列、输出序列、空地，目标序列和当前积木，以及实现一系列的指令。此外还有选择关卡并且保存通关信息、显示游戏界面等基础要求。

**2.具体解决：**

我们用a数组存储输入的积木序列，b数组存储输出序列，c数组存储空地，d数组存储目标序列，用r表示当前积木数，用1024表示当前位置没有积木，用instruction数组和x数组记录下指令。我们声明了inbox等函数，来实现指令。

选择关卡部分我们用文件相关的知识解决，详见“三、选择关卡界面的设计”。

显示游戏界面的函数实现如下：

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps1.jpg) 

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps2.jpg) 

通过计算出控制台的高度和宽度以及设置光标的位置，实现在对应位置打印出机器人空地等图形。moverobot函数实现了对于机器人运行的逐步模拟。具体实现效果可以参见下图以及自行调试。

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps3.jpg) 

**3.扩展功能：**

我们实现了玩家自定义增加关卡的功能。为了主函数的简明性，我们将不同关卡的信息都保存在对应的文件中，可以直接进行读入，从而避免了大量重复的if分支结构，也便于玩家自定义增加关卡。实现代码详见“三、选择关卡界面的设计”。

 

#### 二、工程结构

为了主函数的简明性，我们将文件拆分为function.h,function1.cpp,主函数.cpp三个文件。另外还有一系列的资源文件。

其中function.h文件声明函数和全局变量、结构体（如下图）：

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps4.jpg) 

function1.cpp对于声明的函数进行了定义，主要实现显示界面、指令集、选择关卡等功能，主函数.cpp中调用对应的函数实现游戏功能。

资源文件分别以“level+关卡编号+.txt”和”level+关卡编号+data”命名，前者对应非自定义关卡的正确答案，后者对应各关卡的关卡信息。其中第五关以后文件初始为空，可以由玩家自行设计。

#### 三、选择关卡界面的设计

函数实现如下图：

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps5.jpg) 

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps6.jpg) 

load函数通过声明一个新的结构体vector数组，并且从文件中读入，然后不断加入数组，最后将数组返回，实现从文件中的加载。

chooselevel函数将文件中的信息输出到屏幕上，让用户对前面关卡的通关情况有所了解。实现效果如下图：

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps7.jpg) 

save函数将结构体vector数组中的元素读入文件中并且实现对原文件的覆盖，实现通关信息的记录，并且在关闭后也可以保存。

此外，我们还实现了玩家自定义增加关卡、删除关卡以及重置通关状态的扩展功能。重置通关状态以及增加关卡实现代码如下：

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps8.jpg) 

 

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps9.jpg) 

玩家通过自行读入一组文件数据到“level+关卡编号+data.txt”中并将关卡信息插入结构体数组levels当中，实现了关卡信息的保存。

 

删除关卡实现代码如下：

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps10.jpg) 

 

#### 四、游戏测试

**1、选关界面操作：**

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps11.jpg)![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps12.jpg) 

打开游戏进入选关界面，游戏会提示玩家选择一个关卡。初始状态下只能选择1-4关。如果前置关卡没有完成，而选择了后面的关卡，或者选择了不存在的关卡，游戏会提示当前选择不合理。

在选关界面还可以进行一些其他操作：输入0，会进入新增关卡页面，玩家可以自定义增加关卡；输入999，系统会重置目前的通关状态（所有关卡显示“未通过”）；输入1024，系统会清除新增的自定义关卡及其文件。

**2、关卡准备界面操作（以第二关为例）**

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps13.jpg) 

选择一个关卡，系统从存储中读取这个关卡的配置信息，进入准备界面。系统会询问玩家是要选择用键盘手动输入指令（1）还是用文件输入指令（2）。选择1，则系统询问玩家要输入多少条指令，并且等待玩家输入完所有指令。选择2，输入对应的文件路径，则游戏会根据玩家输入的文件路径，从存储中读取玩家提前预设好的指令文件。如果文件不存在，则提示“不存在对应的文件”。

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps14.jpg)键盘输入

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps15.jpg)文件输入

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps16.jpg)错误文件路径

**3、关卡运行显示（以第二关为例）**

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps17.jpg)运行中

  指令输入完成后，点击回车键进入关卡运行界面。机器人会按照玩家给出的指令运动并完成各项操作。如果检测到无效指令（不在指令集中、不符合该指令运行条件、操作数数量和要求不符、操作数超出范围、操作数不是整数等），则机器人停止运行，在无效指令旁边显示“Error on instruction X”（X是无效指令的编号），关卡结束。

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps18.jpg)不在指令集中

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps19.jpg)运行异常

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps20.jpg)多个操作数

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps21.jpg)操作数超限

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps22.jpg)非整操作数

若没有出现异常指令，则当指令执行完成，或者执行“inbox”指令时输入传送带上没有积木，则关卡结束，系统判定运行结果。如果运行正确，则输出“Success”，否则输出“Fail”。只要关卡正常完成，都会在左下角输出实际执行的指令数。此时按1即可回到选关界面。

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps23.jpg) 

**4、新增关卡操作&清除关卡数据操作**

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps24.jpg) 

在选关界面输入0，即可进入自定义关卡界面。在此界面中按照指示，依次输入输入传送带上的积木数目及提供的数字、输出传送带上的积木数及目标数字、可用的空地数（最多八个）、可用的指令数、可用指令集，全部输入完成后按1返回选关界面，此时可以看到新增的关卡（默认状态是“未通过”）。 ![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps25.jpg)

新增关卡的运行方法与前四个关卡相同。选择新增关卡，进入准备界面，按要求输入指令，即可进入关卡运行界面。

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps26.jpg)

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps27.jpg) 

在选关界面输入1024，即可清除所有新增的自定义关卡，只保留四个基本关卡。输入999，即可清除所有关卡的通关数据，将各关卡设置为“未通过”。

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps28.jpg)![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps29.jpg) 

输入999后的结果         输入1024后的结果

 

#### 五、自由创新关卡：

在三个固定关卡之外，第四关是创新关卡。下面介绍这一关卡的配置文件、输入、输出要求及一种可行思路。

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps30.jpg) 

第四关的配置文件内容为：

8

9 6 7 1 5 0 -2 4

4

16 11 5 -2

3

5

inbox outbox copyto copyfrom add

即：输入序列为：9，6，7，1，5，0，-2，4；输出序列为：16，11，5，-2。可用空地数为3，除sub，jump，jumpifzero外其余指令可用。

参考思路：通过观察可得，16=9+7，11=6+5，5=4+1，-2=0+（-2），即输出序列的第k个数是输入序列中第2k-1和第2k大的数之和。此关卡的难点在于，输入序列中的数字不是按大小顺序排列的，因此利用空地，将这些数字按照合适的先后顺序相加，具有一定技巧性。

一种解法为：inbox，copyto 0，inbox，copyto 1，inbox，add 0，outbox，inbox，copyto 2，inbox，add 1，outbox，inbox，copyto 1，inbox，copyto 0，inbox，add 2，outbox，copyfrom 0，outbox。

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps31.jpg) 

![img](file:///C:\Users\康嘉成\AppData\Local\Temp\ksohtml13732\wps32.jpg) 

 