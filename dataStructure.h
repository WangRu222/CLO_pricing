#pragma once//同一个文件不会被包含多次

#pragma warning(disable:4018)// 有符号/无符号不匹配 警告. 如unsigned int 类型 与 int 类型变量之间的比较。
#pragma warning(disable:4244)// 数据类型转型可能数据丢失。 如讲double转化为int. 可使用static_cast<int>进行强制类型转换。

//该base文件参考了以下文件
//SharedDefines.h---定义了Array1D等


#define NOMINMAX
#include <Windows.h>
//#define NOMINMAX告诉编译器(或实际上是预处理器)跳过min和max的定义,但只有在#include "windows.h"之前执行此操作时才会应用它。

#include <algorithm>//C++标准库：包含了所有vector、list、set、map操作能想到的一些函数,如查找,替换、排序、计数等常用的功能全部在里面
#include <fstream>//C++中的IO库类型
#include <strstream>//C++中C语言风格的输入输出
#include <valarray>
#include <float.h> //C语言标准库头文件，定义了浮点型的范围，精度。用于数值分析。
#include <string>
#include <cassert>
using namespace std;//valarray是C++ STL标准库；可以添加此语句，也可以使用std::valarray

//1. 使用#define定义常量和常用数学函数

//#define  标识符  常量   //注意, 最后没有分号
//凡是以“#”开头的均为预处理指令,预编译不是编译，而是编译前的处理。这个操作是在正式编译之前由系统自动完成的。预编译所执行的操作就是简单的“文本”替换。
// 
//#define与typedef的区别
//#define用标识符表示一个字符串，成为宏； typedef用于给一个变量起个新的名字，便于阅读，发生在编译阶段。

//#define与const定义常量的区别
//#define在预处理阶段替换；const在编译时确定值
//#define无类型，不检查类型安全性；const有数据类型，编译时检查
//#define多次用到多次拷贝；const在静态存储区分配内存，程序运行过程中内存中只有一个拷贝

#define PRECONDITION(a)     assert( (a) != 0 ) /* Check pre- and post-conditions */
#define POSTCONDITION(a)    assert( (a) != 0 )
#define MAX(a,b)	( (a)<(b) ? (b) : (a) )
#define MIN(a,b)	( (a)<(b) ? (a) : (b) )
#define MIN4(a,b,c,d)	( MIN( MIN((a),(b)) , MIN((c),(d)) ) ) //rdv.cpp需使用
#define ABS(a)		( (a)< 0  ?-(a) : (a) )
#define SGN(a)		( (a)< 0  ? -1  :  1  )
#define SWAP(a,b)   {temp=(a); (a)=(b); (b)=temp;} //原先定义在NumUtilities.cpp中
#define EPS         (1.e-8 )
#define EPS1		( 1e-8 )
#define MAX_STR	    (1<<12)		// Maximum string length. 2**12=4096. 表示将二进制1向左移动的位数
#define JMAX        200//原先定义在NumUtilities.cpp的头部
#define	ROOT_2PI	( 2.506628274631 )//原先定义在util.h; 在CumNorm.h中同样定义该值，#define DBA_SQRT2PI
#define MAXN		(1000)  //以下两个在lu.cpp中定义的
#define	MM(i,j)		(M[(i)*n+(j)])
#define	STATUS_MAX	(250)	// Maximum length of Excel status string.
#define EXITS(s) {sprintf(status,"%.*s",STATUS_MAX,(s)); return;}
#define nrerror		throw
#define getInt(a)		(a<= 0 ? ceil(a) : floor(a))
#define positiveinf  1e8
#define negativeinf -1e8


//-----------以下三个函数在QFrequency中用到------
//本身定义在Utility.h/.cpp中，为了不在次引入，在此就单独定义了三个函数
void  ToUpper(string& s);
void ToLower(string& s);
//匹配部分字符串
size_t MatchPS(const char* szPermittedString[], unsigned int nNumPermitted, const char* szPartialString, size_t& nMatchedIndex);



enum class quantEnum
{
	//product category
	Equity = 1,
	FX =2,
	FixedIncome = 3,
	Credit = 4,
	Commodity =5,
	

	//变量：greekflag/all_greek_flag  : all_greek_flag=1, calculate vega, rho and epsilon;  all_greek_flag=2, NO calculate vega, rho and epsilon;
	//变量：payAtEnd/payoff_at_end,in_performance,AddCallableDates,DailyFixFlag/daily_fixing_flag,m_JumpD_Flag,T_equal_zero_triggered,pass_divi_flag,QuickSortNeeded
	//	   pass_divi_flag: 
	//						Yes:take dividends up to the delivery.
	//						No :take dividends up to the expiry.
	Yes = 1,
	No,

	Put = 0,
	Call = 1,

	callOption = 1, //在PDESolver中的变量m_call_put_flag需要设置成callOption和putOption; 而不是上面的Call,Put
	putOption = -1,

	//============barrier option BEG===========
	// Barrier
	// 变量：barrier_touched
	NotTouched = 0,
	Touched,

	UpOut = 1,//single barrier option type
	UpIn,
	DnOut,
	DnIn,

	DoubleKnockOut = 1,//double barrier option type
	DoubleKnockIn = 2,

	continuousMonitor = 0,
	discreteMonitor = 1,

	singleBarrier = 1,
	doubleBarrier = 2,
	//============barrier option END===========


	//===========ansian option BEG============
	fixedStrike = 0,
	floatStrike = 1,

	GeometricAverage = 0,
	ArithmeticAverage = 1,

	// Option type.
	European = 1,
	American,
	Bermudan,
	CallPut_able,
	Euro_JumpD,        // jump diffusion.

	////期权定价模型,原先定义在OptionBase.h/.cpp文件中
	ZB = 1,
	BK,
	HW,

	//===========ansian option END============

	//============Callable bull bear contracts
	callableBull = 0,
	callableBear = 1,

	residualType_N = 0,
	residualType_R = 1,
	//============callable bull bear contracts

	//====================date.h date.cpp====
	basis_30E_360 = 0,
	basis_30_360 = 1,
	basis_actual_360 = 2,
	basis_actual_365 = 3,
	basis_actual_actual = 4,
	basis_1_1_y = 5,//一年
	basis_1_2_y = 6,//半年:0.5
	basis_1_4_y = 7,//一个季度：0.25
	basis_actual_365F = 8,
	//====================date.h date.cpp====

	//==================ACCUMULATOR.CPP中用到的==========
	daily = 0,
	weekly,
	monthly,
	quarterly,
	semiannually,
	annually,

	zero,//在IRS中调用
	quarter,
	annual,
	maturity,

	longPosition = 1,
	shortPosition = -1,
	//==================ACCUMULATOR.CPP中用到的==========

	//变量：quantoFlag
	// A quanto option is an option denominated in a currency other than the currency in which the underlying asset is traded.
	NonQuanto = 1,
	Quanto,
	Compo,



	// Rebate
	//变量：rebate_method
	PayAtTouch = 1,
	PayAtExpiry,

	LookBack = 1,
	HindSight,
	CallMinPutMax,

	L_FactorTree = 1,
	PureImpliedTree,

	FwdSkew = 1,
	FwdATMVol,

	Term_L = 1,
	Fwd_Fwd_L,

	// Option settlement.
	// 变量：cash_physical
	CashSettle = 1,
	PhysicalSettle,



	// For callable bonds.
	NonCallableNonPutable = 0,//added by GL
	Callable = 1,
	Putable,

	// Volatility dynamics.
	//变量：VolMethodFlag/vol_method_flag/volMethod(convertible bond)
	//sticky 粘性的
	StaticVol = 1,      // Static Vol Surface.
	StickyDelta,        // Vol Surface Moves With Spot -- Convolution.
	StickySkew,         // ATM-Vol From The Static Vol Surface, Skew Moves With Spot -- Sophis.

	//变量：divTreatmentFlag,ModelFlag
	// Model methods used by the PDE solver.
	DiscreteDiv = 1,    // Handle discrete dividends rigorously.
	ProportionalDiv,    // Turn discrete dividends into proportional dividends.
	ContinuousYield,    // Merge discrete dividends with repo and treat as continuous yield.

	// Boundary searching for PDE.
	UpLimit = 1,
	LowLimit,

	// PDE attached tail model.
	// 变量：m_tail_model
	None = 1,		//	No tail.
	AsianSimple = 2,		//	Use simple Asain - continuous moment matching.
	AsianCG = 3,		//	Use conditioning geometric Asian model.
	LookbackFlatVol = 4,		//	Using flat vol
	LookbackCB1Vol = 5,		//	Using cascading barrier and one vol  for barrier
	LookbackCB2Vol = 6,		//	Using cascading barrier and two vols for barrier

	//For Barrier Vol model
	VolAtStrike = 1,
	VolAtBarrier = 2,
	AsRainbowBarrier = 3,	//	Use rainbow barrier option
	FromRBProb = 4,	//	Using rainbow barrier option
	FromRBProbCorr = 5,	//	Using rainbow barrier option

	//For Lookback Vol model
	FlatVol = 1,
	WithSkew1 = 2,	//	Cascading Barrier with simple barrier option
	WithSkew2 = 3,	//	Cascading Barrier with rainbow barrier option

	// Which vol functional form: Tanh or PolyBlend.
	VolFuncTanh = 55,
	VolFuncPoly = 33,


	//add by gl 2022-03023; vol_fitting_flag
	linearVariance = 1,
	linearVol = 2,

	//add by GL 20220504
	dateCon_MFBD = 0,//multiType.h , Modified following business day.

	// Multi-asset products, the list goes on ...
	//变量：which_model
	WorstOf = 1,
	BestOf, 
	OneTouchSum,

	//===来源于SingleStockBase.h
	Historic = 1,
	RiskNeutral,

	ConstrainFwd = 1,
	ConstrainBoth,         // Constrain both forward and vol.
};


// Accrual basis.
//typedef enum {
//	ANFPED_basis_30E_360 = 0,
//	ANFPED_basis_30_360 = 1,
//	ANFPED_basis_actual_360 = 2,
//	ANFPED_basis_actual_365 = 3,
//	ANFPED_basis_actual_actual = 4
//} ANFPED_basis;

const double pi = 3.141592653589790;
const double days_pa = 365.;
const int output_rows = 7;
const int output_columns = 1;
//inline内联函数，解决频繁调用函数对栈空间的消耗问题。
//内联是以代码膨胀复制为代价，仅仅省去了函数调用的开销，从而提高函数的执行效率。如果执行函数体内代码的时间，相比于函数调用的开销较大，那么效率的收获会很少。
//函数体内不能出现循环

//模板函数定义方式：template <class T> T f(T a,T b){}
template <class T>T inline maxi(T a, T b) { return a > b ? a : b; }
template <class T>T inline mini(T a, T b) { return a < b ? a : b; }
template<class T>inline int signof(T& a) { if (a < 0) return(-1); return(1); }

//C++中数组存储的几种方式
//内置数组：int a[40];大小固定，速度快
//数组指针： int *a; a = new int[40]; 这里的a可以等价于内置数组；两个a均表示数组首个元素的地址。
//vector: #include<vector> vector<int> a(N); a.push_back(888); 使用new/delete进行内存管理； 长度可变，灵活，效率低
//array: #include<array> array<int,2> a = {1,2}; 长度固定，更安全接口，效率同内置数组。
//valarray: #include<valarray> valarray<int> a(10); 面向数值计算的数组； 可通过resize改变大小，注意调整大小后，数据将丢失。shift/cshift可用于数据的平移
typedef valarray< double > Array1D; //注意：Array1D x(0.5,10); x.resize(10,0.5); //初始化时，前者为value,后者为数量；resize时，前者为数量，后者为value
typedef valarray< Array1D > Array2D;
typedef valarray< Array2D > Array3D;
typedef valarray< int > Array1I;
typedef valarray< Array1I > Array2I;
typedef valarray< long > Array1L;
typedef valarray< Array1L > Array2L;
typedef valarray<string> Array1S;
ostream& operator<<(ostream&, const Array1D&);
ostream& operator<<(ostream&, const Array2D&);

//定义一些关于Array2D的函数=========
double dot(const Array1D& a1, const  Array1D& a2);//向量点击
Array2D dot(const Array2D& m1, const  Array2D& m2);//矩阵乘积
Array2D dot_element(const Array2D& m1, double x);//常数乘以矩阵的每一个元素
Array1D dot(const Array2D& m1, const  Array1D& a1);//矩阵乘向量
Array1D dot_element(const Array1D& a1, const  Array1D& a2);//元素相乘
Array1D plus_element(const Array1D& a1, const  Array1D& a2);//元素相乘
Array2D plus_element(const Array2D& m1, const  Array2D& m2);//元素相乘
Array2D dot_element(const Array2D& m1, const  Array2D& m2);//元素相乘
Array2D trans(const Array2D& m);//将Array2D转置
double trace_Array2D(const Array2D& m);//对角线元素之和
Array1D minus_Array1D(const Array1D& first, const Array1D& second);//数组相减
double sum_Array1D(const Array1D& first);//数组元素求和
Array1D getPart_Array1D(Array1D& originalArr, size_t begIndex, size_t endIndex);//返回[begIndex,endIndex]之间的子数组，注意与python的区别:[begIndex,endIndex)
Array2D getPart_Array2D(Array2D& originalArr, size_t begIndex, size_t endIndex);
double getNorm2(Array1D&);//计算2范数
double maxDiag(Array2D&);//对角线最大元素




//2. 定义常用的数据结构

// ************************************************************************************
// Memory allocation & other common functions.
// ************************************************************************************


//2.1 可变长的一维数据结构
//tvec---可变长度的数组;模板
//dvec---继承于tvec<double>
//ivec---继承于tvec<int>
//cvec---继承于tvec<char> 可append的字符串              //本身在util.h中未定义，在utils.h有定义；在excel.h中用到cvec
//cvecv---继承于tvec<cvec>  可变长的一系列字符串构成的数组

//2.2 可变长的二维数据结构
//imat---可变尺寸的二维数组，存放int型数值
//dmat---可变尺寸的二维数组，存放double型数值
//dmatv---应该书一系列dmat构成的数组，但是为什么用二维指针

//自定义可变长数组的常用接口
//1. 构造函数：由一个整数n1初始化，并开辟长度为n1的空间
//2. 构造函数：可通过Array1D,Array2D等构造一维可变长数组
//3. resize(n0): 调整可变长数组长度为n0，n0<n1则丢弃后面的(n1-n0)个值;n0>n1则补零
//4. 隐式转换operator: tvec对象可类似于内部对象p,通过[],*来取p内部的值
//5. 复制构造函数：dvec a(b); 其中b是一个已经存在的dvec对象
//6. operator=重载：dvec a = b;



// Variable size vector.  Behaves as Type*.
template<class Type> class tvec {
	public:

		//=============================4类构造函数============================
		//1. 默认构造函数+自定义构造函数结合。两种方式定义对象：1. tvec t0；2.tvec t0(5);
		//由于该定义方式包含了默认构造函数，所以不能再定义一个默认构造函数：tvec ():n(0),p(new Type[0]){};
		tvec(size_t n1 = 0) : n(n1), p(new Type[n1]) {};
		//构造函数初始化列表；初始化列表的成员初始化顺序:C++ 初始化类成员时，是按照声明的顺序初始化的，而不是按照出现在初始化列表中的顺序。
		// 
		//2. 复制构造函数
		tvec(const tvec& v) : n(v.n), p(v.n > 0 ? new Type[v.n] : 0)
		{
			size_t	i;
			for (i = 0; i < v.n; i++) p[i] = v.p[i];
		}
		//3. 操作符=的重载
		tvec& operator=(const tvec& v)
		{
			size_t		i;
			resize(v.n);
			for (i = 0; i < v.n; i++) p[i] = v.p[i];
			return *this;
		}
		//============================析构函数================================
		~tvec(void) 
		{
			//printf("%f\n", p[0]);
			delete[] p; 
			//printf("delete tcev\n");
		}

		//============================其他自定义函数===========================

		//----------------------------f1:resize尺寸，而不改变原值---------------
		void resize(size_t n0) {
			//区别于valarray中的resize: 
			//valarray的resize重设长度，并且重新初始化。myarray.resize(3,1);重设为3个1.没有1的话，默认3个0. 
			//这里的resize保留原数组中的值，多了去掉；不够补零。
			size_t		i;
			Type* p0 = new Type[n0]{};

			for (i = 0; i < (n < n0 ? n : n0); i++) p0[i] = (*this)[i];//将本来位置的元素还放置于本来位置
			for (i = (n < n0 ? n : n0); i < n0; i++) p0[i] = 0.0;//如果长度变长，补0；
			delete[] p;
			p = p0;
			n = n0;
		}

		//resize尺寸，新的值均为v0
		void resize(size_t n0, Type v0) {
			//区别于valarray中的resize: 
			//valarray的resize重设长度，并且重新初始化。myarray.resize(3,1);重设为3个1.没有1的话，默认3个0. 
			//这里的resize保留原数组中的值，多了去掉；不够补零。
			size_t		i;
			Type* p0 = new Type[n0];
			for (i = 0; i < (n < n0 ? n : n0); i++) p0[i] = v0;//将本来位置的元素还放置于本来位置
			for (i = (n < n0 ? n : n0); i < n0; i++) p0[i] = v0;//如果长度变长，补0；
			delete[] p;
			p = p0;
			n = n0;
		}

		//---------------------------f2：隐式转换，将类对象转为内部的数组--------------------
		//operator的使用方法之一：隐式类型转换符operator casting; 另一种常用用处为：操作符重载即operator overloading
		//在需要的地方tvec对象可以当作里面的变量p使用，即tvec a; a[0]就是取得p所指向的数组中的值。
		inline operator Type* (void) const { return p; }	// Violate const.

		//----------------------------f3:push_back,利用resize在默认添加值-------------------

		void push_back(Type v0)
		{
			resize(n + 1);//长度增加一
			p[n-1] = v0;
		}
		void pop_first()
		{
			if (n == 1) { delete[] p; n = 0; }
			else if(n > 1)
			{
				for (size_t i = 0; i < n - 1; i++)p[i] = p[i + 1];
				resize(n - 1);
			}
		}
		void pop_back()
		{
			if(n>0) resize(n - 1);
		}
		void push_first(Type v0)
		{
			resize(n + 1);
			for (size_t i = n - 1; i > 0; i--)p[i] = p[i - 1];
			p[0] = v0;

		
		}
		void push_inorder(Type v0, int order,bool repeat)
		{
			//order =1,-1；分别表示按照递增或递减的方式存储
			//repeat = true,false分别表示可以存储重复值，或不可以存储重复值.
			if (n == 0)push_back(v0);
			if (repeat == true || isContain(v0) == false)
			{
				if (order == 1)//默认原数组是按照递增排列的
				{
					int k = -1;//需要插入的位置
					for (int i = 0; i < n; i++)if (v0 <= p[i]) { k = i; break; }

					if (k != -1)push(v0, static_cast<size_t>(k));
					else push_back(v0);
				}
				else//默认原数组是按照递减排列的
				{
					int k = -1;
					for (int i = 0; i < n; i++)if (v0 >= p[i]) { k = i;  break; }
					if (k != -1)push(v0, static_cast<size_t>(k));
					else push_back(v0);
				}
			}

		}

		void sort(int order)
		{
			//order=1递增；order=-1递减
			for(size_t i = 0; i <n-1; i++)
				for (size_t j = i + 1; j < n; j++)
				{
					Type temp;
					if (order == 1 && p[j] < p[i]) { temp = p[i]; p[i] = p[j]; p[j] = temp; }
					else if (order == -1 && p[j] > p[i]) { temp = p[i]; p[i] = p[j]; p[j] = temp; }
				}
		
		}
		void pop(size_t k)
		{
			//在第k个位置的元素剔除
			if (k < 0 || k >n - 1) throw"error pop index";
			else if (k == 0) pop_first();
			else if (k == n - 1) pop_back();
			else
			{
				for (size_t i = k; i < n-1; i++)p[i] = p[i + 1];
				resize(n - 1);
			}
		
		}
		void push(Type v0, size_t k)
		{
			//在第k的位置处添加元素v0
			if (n == 0 || k >= n) push_back(v0);//如果k超过了元素的个数，则总是在最后面的位置插入
			else if (k <= 0) push_first(v0);//如果k为负，总是在第一个位置插入
			else
			{
				resize(n + 1);
				for (size_t i = n - 1; i > k; i--)p[i] = p[i - 1];
				p[k] = v0;
			}
			
		}

		bool isContain(Type v0)
		{
			if (n <= 0) return false;
			else 
			{
				for (size_t i = 0; i < n; i++)if (p[i] == v0) return true;
				return false;
			}
		}

		size_t size() { return n; }

		//==============================成员变量==================================
		size_t		n;//数组的长度
		Type*   p;//数组长度的首地址



	private:
};

// Variable size vector.  Behaves as double*.
class dvec : public tvec<double> {
public:
	//==================================构造函数定义===================
	//1.子类不继承父类的构造函数；
	//2.如果父类构造函数含参，子类必须显式调用父类的构造函数；调用方法表示为":father(n1)". 以下三个构造函数均实现了父类构造函数的调用。
	
	//默认构造函数
	dvec(size_t n1 = 0) : tvec<double>(n1) {};//A(b)实际上是做的是用b初始化A的成员x;即x=b; 是初始化列表方式。
	dvec(size_t n1,double v0) : tvec<double>(static_cast<int>(MAX(n1,0))) {
		//printf("using copy constructor(Array1D)\n");
		for (int i = 0; i < MAX(n1, 0); i++) (*this)[i] = v0;
	}

	//copy构造函数：有以下两种使用方式
	// Array1D a0; dvec d0 = a0;或者dvec d0(a0);
	dvec(const Array1D& a);//用Array1D构造dvec
	dvec(const dvec& a);
	dvec(const initializer_list<double>& _Ilist)
	{
		//printf("using copy constructor(initializer_list)\n");
		n = static_cast<int>(_Ilist.size());
		resize(n);//开辟n长度的空间
		int i = 0;
		for (auto iter = _Ilist.begin(); iter < _Ilist.end(); iter++) { p[i] = *iter; i++; }
	}

	dvec& operator=(const dvec& a)
	{
		//printf("use operator overload(Array1D)\n");
		n = static_cast<int>(a.n);
		resize(n);
		for (int i = 0; i < n; i++)p[i] = a[i];
		return *this;
	}

	//操作符=的重载，将Array1D对象赋值给已经存在的dvec对象
	dvec& operator=(const Array1D& a)
	{
		//printf("use operator overload(Array1D)\n");
		n = static_cast<int>(a.size());
		resize(n);
		for (int i = 0; i < n; i++)p[i] = a[i];
		return *this;
	}
	//操作符=的重载，将initializer_list对象赋值给已经存在的dvec对象
	dvec& operator=(const initializer_list<double>& _Ilist)
	{
		//printf("use operator overload(initializer_list)\n");
		n = static_cast<int>(_Ilist.size());
		resize(n);//开辟n长度的空间
		int i = 0;
		for (auto iter = _Ilist.begin(); iter < _Ilist.end(); iter++) { p[i] = *iter; i++; }
		return *this;
	}

	dvec(const Array2D& a);//用Array2D构造dvec
	//================================其他自定义函数===================
	//------------------------------f1:将dvec对象转化为Array1D对象-----
	Array1D getArray1D()
	{
		Array1D a0(n);
		for (size_t i = 0; i < n; i++)a0[i] = p[i];
		return a0;
	}
	double sum();//求和
private:
	//dvec(double);//暂无定义！？
};
ostream& operator<<(ostream&, const dvec&);

// Variable size vector.  Behaves as int*.
class ivec : public tvec<int> {
public:
	ivec(size_t n1 = 0) : tvec<int>(n1) {};
	ivec(const Array1I& a);
	ivec(const Array2I& a);//用Array2D构造ivec
	Array1I& getArray1I()
	{
		Array1I a0(n);
		for (size_t i = 0; i < n; i++)a0[i] = p[i];
		return a0;
	}

private:
	//ivec(double);//暂无定义
};

//Variable size Vector. 类似于 char*
//C++存储字符串的几种方式
// char str0[2] = {'a','b','\0'};
// char str1[] = "ab\0";//以上两种为数组，最好加上\0
// char *str2 = "ab"; //char * 与 char []的区别：char*是变量，值可以改变， char[]是常量，值不能改变

//strlen, strcpy, strncpy定义在string.h中。
//string.h, cstring, string 三个库的区别：
//string.h文件是C语言的库；cstring是C++对string.h的简略升级与包装;
//string就与前面两个有本质差别了。它是C++自己开发封装的类，同样用于字符串操作，其中用到了很多的操作符重载等方法，实现方法和C标准库中的string.h有很大差别。


//Variable size Vector. Behaves as char*. 
//可以调用append来扩展原字符串
class cvec : public tvec<char> {
public:
	cvec(int n1 = 0) : tvec<char>(n1) {};
	//strlen,strcpy,strncpy三个均定义在string.h中，这里未引入string.h也可以使用，是在哪里引入的!?
	//strlen:得出的结果不包括最后的\0;所以要加上1；
	//strcpy:把含有'\0'结束符的字符串复制到另一个地址空间，返回值的类型为char*;前参数为目标地址，后参数为数据来源地址。
	//strncpy: 把来源字符串前n个字符复制到另一个地址空间，返回值的类型为char*;前参数为目标地址，后参数为数据来源地址。
	cvec(const char* s) : tvec<char>(s ? static_cast<int>(strlen(s) + 1) : 0) { if (s) strcpy(p, s); };
	cvec(const char* s, int n) : tvec<char>(n + 1) { strncpy(p, s, n); p[n] = 0; };
	void append(const char* s); //该函数是从utils.cpp中复制到util.cpp中
};


// Vector of cvec:
class cvecv : public tvec<cvec> {
public:
	cvecv(int n2 = 0) : tvec<cvec>(n2) {};//子类必须调用父类的含参构造函数
};
// ************************************************************************************

// Variable size matrix of integers
class imat {
public:
	//imat(int r1, int c1) : r(r1), c(c1), p(new int[r1 * c1]) {}
	//上面的语句出现警告using operator"*" on a 4 byte value and then casting the value to a 8 byte value.
	//原因int[]中放入的变量是size_t类型，占用8 字节； 而两个int相乘仍是int类型，占用4个字节；将4字节变量放到本应该放8字节的位置就出现了警告。

	imat(int r1, int c1) : r(r1), c(c1), p(new int[static_cast<long>(r1) * static_cast<long>(c1)]) {}//4字节强制转换为8字节
	//32位编译器：int/float/unsigned int/long/unsigned long: 4字节； long long/double：8字节
	//64位编译器: int/float/unsigned int:4字节； long/long long/unsigned long/double:8字节
	~imat(void) { delete[] p; }
	void resize(int r, int c);
	//const限定了 只能读取，不能修改成员变量
	inline int* operator[](int r_) const { return p+ static_cast<long>(r_*c); }
	inline operator int* (void) const { return p; }	

	//成员变量：行，列，起始指针
	int	r;
	int	c;	
	int* p;
private:
	//以下两个函数均为自己定义，之前只是声明，未定义。
	imat(const imat& d);//复制构造
	imat& operator=(const imat&);//operator=操作符重载
};





// ************************************************************************************

// Variable size matrix
//创建一个可变size的二维double矩阵
//矩阵的求逆、线性方程组求解的函数定义在Numerics.h/.cpp中
class dmat 
{
	public:

		dmat() : r(0), c(0), p(0) {}
		dmat(size_t r1, size_t c1) : r(r1), c(c1), p(new double[r1 * c1]) { init(); } //用长度，宽度构造一个矩阵。成员函数后面加冒号表示赋值
		dmat(const Array2D& a); //用自定义个valarray<valarray<double>>的类型构造dmat
		dmat(const dmat& d);
		dmat& operator=(const dmat&);

		~dmat(void) {
			//printf("delete dmat: %d,%d,%f,%04x\n",r,c,p[0],p);
			delete[] p; 
		}

		void resize(size_t r, size_t c); //可放大：放大时补零；可缩小：缩小时维持原位置不变
		void transpose(void);//转置

		//-----------2022-03-04添加，增加求逆等运算--------------
		void init() { for (size_t i = 0; i < rows() * cols(); i++) p[i] = 0.0;  //printf("\n new: %d,%d,%d\n", p, r, c);
		}
		void set_default_values(double x) {
			for (size_t i = 0; i < rows() * cols(); i++) p[i] = x;  //printf("\n new: %d,%d,%d\n", p, r, c);
		}
		size_t size() const { return static_cast<size_t>(r * c); }
		bool null() { return (size() ? false : true); }
		double norm(int);//未包括所有范数
		bool isSizeEqual(dmat& x);
		size_t rows() const { return r; }
		size_t cols() const { return c; }
		double maxDiag();
		double* pointer() const { return p; }
		Array1D row(size_t _r) const;//获取第_r行的值, _r从0到r-1,否则报错
		Array1D col(size_t _c) const;//获取第_c列的值, _c从0到c-1,否则报错
		double operator()(size_t _r, size_t _c); //用括号(1,1)取值
		const double operator()(size_t _r, size_t _c) const; //用括号(1,1)取值
		dmat& operator=(double dVal);//矩阵所有元素赋常值
		
		dmat& operator=(const Array2D&);
		bool operator==(const dmat& cThat) const;
		dmat& operator+=(dmat& x);//矩阵对应元素上+/-/*//另一个矩阵的相应元素
		dmat& operator-=(dmat& x);
		dmat& operator*=(dmat& x);
		dmat& operator/=(dmat& x);
		//-----------2022-03-04添加，增加求逆等运算--------------

		inline double* operator[](int r_) const { return p +r_*c; }//可以通过mat[i][j] = 888.0给矩阵赋值
		//返回一个指向double的指针，指针加减法表示在数组中平移相同整数的位置；
		//(*this)[i][j] 首次使用平移到第i行开头的第一个元素-->（*this）[i] 返回的是该dmat对象中的数组指针-->再加[j]表示数组指针向后平移j个位置
		//this[i][j]这个应该是返回指向某个特定元素的指针，取值不应该是*(this[i][j]),应该与(*this)[i][j]等价吧！？见下一个隐式转化函数

		inline operator double* (void) const { return p; }	// Violate const.隐式转换，将类对象转化为内部的指针变量p,所以以上的(*this)返回的是p
		size_t			r;
		size_t			c;	// Can't change this once data entered.
		double*         p;
	private:
		
		
};

//----------矩阵的相应操作-----
dmat matrix_Product(dmat& left, dmat& right);//矩阵相乘
dmat operator*(dmat& left, dmat& right);//矩阵相乘
dmat dot_Product(dmat& left, dmat& right);//对应元素相乘
dmat operator-(dmat& left, dmat& right);//矩阵元素相减
dmat operator+(dmat& left, dmat& right);//矩阵元素相加
dmat operator/(dmat& left, dmat& right);//矩阵元素相除
dmat operator-(dmat& left, double x);//矩阵元素减常数
dmat operator*(double x,dmat& left);//矩阵元素乘以特定值
dmat transpose(dmat& x);//转置
ostream& operator<<(ostream&, const dmat&);
//istream& operator>>(istream& is, dmat& tThis);
//----------矩阵的相应操作-----




/* 在ED_Analytics.h中，定义在MemoryAllocator.cpp中的开辟二维数组的程序 */
//一般没必要用，直接用dmat类对象即可。
double** New2DMatrix(long nrow, long ncol);
void Delete2DMatrix(double** m);




// Vector of matrices.
//表示由一列dmat对象构造的数组
class dmatV 
{
	public:
		dmatV(int n, const Array2D** mat = 0);
		~dmatV(void);
		inline operator const dmat** (void) const { return p; }
		int	n;//
	private:
		const dmat** p;//dmat构成的数组，不是只要一个*就可以了吗？
		//首先dmat表面上是一个二维矩阵
		//dmat** p表示的是一个指向“一系列dmat对象地址”的指针；p指向的指针所指向的dmat对象在内存中不一定连续
		//dmat*p ；如果p表示dmat数组的首地址，那么这些dmat对象在内存中是连续的。
	private:
		//dmatV(const dmatV&);
		//dmatV operator=(const dmatV&);
};


// N<=3 dimensional rectangle of numbers.
class dcube
{
	public:
		dcube(int a_ = 1, int b_ = 1, int c_ = 1) : a(a_), b(b_), c(c_),
			p(new double[a * b * c]) {
			if (!p) throw " Out of memory";
		}
		~dcube(void) { delete[] p; }
		inline double& operator()(int i = 0, int j = 0, int k = 0) {
			return p[i * b * c + j * c + k];
		}
		inline double operator()(int i = 0, int j = 0, int k = 0) const {
			return p[i * b * c + j * c + k];
		}
		inline double* ptr(int i = 0, int j = 0, int k = 0) const {	// Violate const.
			return p + i * b * c + j * c + k;
		}
		inline double* ptr(int i = 0, int j = 0, int k = 0) {
			return p + i * b * c + j * c + k;
		}
		int		a, b, c;
		double* p;
		//inline friend void swap(dcube& a, dcube& b) { double* p = a.p; a.p = b.p; b.p = p; }
	private:
		//dcube(const dcube&);
		//dcube& operator=(const dcube&);
};












