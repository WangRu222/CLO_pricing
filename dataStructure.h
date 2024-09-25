#pragma once//ͬһ���ļ����ᱻ�������

#pragma warning(disable:4018)// �з���/�޷��Ų�ƥ�� ����. ��unsigned int ���� �� int ���ͱ���֮��ıȽϡ�
#pragma warning(disable:4244)// ��������ת�Ϳ������ݶ�ʧ�� �署doubleת��Ϊint. ��ʹ��static_cast<int>����ǿ������ת����

//��base�ļ��ο��������ļ�
//SharedDefines.h---������Array1D��


#define NOMINMAX
#include <Windows.h>
//#define NOMINMAX���߱�����(��ʵ������Ԥ������)����min��max�Ķ���,��ֻ����#include "windows.h"֮ǰִ�д˲���ʱ�Ż�Ӧ������

#include <algorithm>//C++��׼�⣺����������vector��list��set��map�������뵽��һЩ����,�����,�滻�����򡢼����ȳ��õĹ���ȫ��������
#include <fstream>//C++�е�IO������
#include <strstream>//C++��C���Է����������
#include <valarray>
#include <float.h> //C���Ա�׼��ͷ�ļ��������˸����͵ķ�Χ�����ȡ�������ֵ������
#include <string>
#include <cassert>
using namespace std;//valarray��C++ STL��׼�⣻������Ӵ���䣬Ҳ����ʹ��std::valarray

//1. ʹ��#define���峣���ͳ�����ѧ����

//#define  ��ʶ��  ����   //ע��, ���û�зֺ�
//�����ԡ�#����ͷ�ľ�ΪԤ����ָ��,Ԥ���벻�Ǳ��룬���Ǳ���ǰ�Ĵ����������������ʽ����֮ǰ��ϵͳ�Զ���ɵġ�Ԥ������ִ�еĲ������Ǽ򵥵ġ��ı����滻��
// 
//#define��typedef������
//#define�ñ�ʶ����ʾһ���ַ�������Ϊ�ꣻ typedef���ڸ�һ����������µ����֣������Ķ��������ڱ���׶Ρ�

//#define��const���峣��������
//#define��Ԥ����׶��滻��const�ڱ���ʱȷ��ֵ
//#define�����ͣ���������Ͱ�ȫ�ԣ�const���������ͣ�����ʱ���
//#define����õ���ο�����const�ھ�̬�洢�������ڴ棬�������й������ڴ���ֻ��һ������

#define PRECONDITION(a)     assert( (a) != 0 ) /* Check pre- and post-conditions */
#define POSTCONDITION(a)    assert( (a) != 0 )
#define MAX(a,b)	( (a)<(b) ? (b) : (a) )
#define MIN(a,b)	( (a)<(b) ? (a) : (b) )
#define MIN4(a,b,c,d)	( MIN( MIN((a),(b)) , MIN((c),(d)) ) ) //rdv.cpp��ʹ��
#define ABS(a)		( (a)< 0  ?-(a) : (a) )
#define SGN(a)		( (a)< 0  ? -1  :  1  )
#define SWAP(a,b)   {temp=(a); (a)=(b); (b)=temp;} //ԭ�ȶ�����NumUtilities.cpp��
#define EPS         (1.e-8 )
#define EPS1		( 1e-8 )
#define MAX_STR	    (1<<12)		// Maximum string length. 2**12=4096. ��ʾ��������1�����ƶ���λ��
#define JMAX        200//ԭ�ȶ�����NumUtilities.cpp��ͷ��
#define	ROOT_2PI	( 2.506628274631 )//ԭ�ȶ�����util.h; ��CumNorm.h��ͬ�������ֵ��#define DBA_SQRT2PI
#define MAXN		(1000)  //����������lu.cpp�ж����
#define	MM(i,j)		(M[(i)*n+(j)])
#define	STATUS_MAX	(250)	// Maximum length of Excel status string.
#define EXITS(s) {sprintf(status,"%.*s",STATUS_MAX,(s)); return;}
#define nrerror		throw
#define getInt(a)		(a<= 0 ? ceil(a) : floor(a))
#define positiveinf  1e8
#define negativeinf -1e8


//-----------��������������QFrequency���õ�------
//��������Utility.h/.cpp�У�Ϊ�˲��ڴ����룬�ڴ˾͵�����������������
void  ToUpper(string& s);
void ToLower(string& s);
//ƥ�䲿���ַ���
size_t MatchPS(const char* szPermittedString[], unsigned int nNumPermitted, const char* szPartialString, size_t& nMatchedIndex);



enum class quantEnum
{
	//product category
	Equity = 1,
	FX =2,
	FixedIncome = 3,
	Credit = 4,
	Commodity =5,
	

	//������greekflag/all_greek_flag  : all_greek_flag=1, calculate vega, rho and epsilon;  all_greek_flag=2, NO calculate vega, rho and epsilon;
	//������payAtEnd/payoff_at_end,in_performance,AddCallableDates,DailyFixFlag/daily_fixing_flag,m_JumpD_Flag,T_equal_zero_triggered,pass_divi_flag,QuickSortNeeded
	//	   pass_divi_flag: 
	//						Yes:take dividends up to the delivery.
	//						No :take dividends up to the expiry.
	Yes = 1,
	No,

	Put = 0,
	Call = 1,

	callOption = 1, //��PDESolver�еı���m_call_put_flag��Ҫ���ó�callOption��putOption; �����������Call,Put
	putOption = -1,

	//============barrier option BEG===========
	// Barrier
	// ������barrier_touched
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

	////��Ȩ����ģ��,ԭ�ȶ�����OptionBase.h/.cpp�ļ���
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
	basis_1_1_y = 5,//һ��
	basis_1_2_y = 6,//����:0.5
	basis_1_4_y = 7,//һ�����ȣ�0.25
	basis_actual_365F = 8,
	//====================date.h date.cpp====

	//==================ACCUMULATOR.CPP���õ���==========
	daily = 0,
	weekly,
	monthly,
	quarterly,
	semiannually,
	annually,

	zero,//��IRS�е���
	quarter,
	annual,
	maturity,

	longPosition = 1,
	shortPosition = -1,
	//==================ACCUMULATOR.CPP���õ���==========

	//������quantoFlag
	// A quanto option is an option denominated in a currency other than the currency in which the underlying asset is traded.
	NonQuanto = 1,
	Quanto,
	Compo,



	// Rebate
	//������rebate_method
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
	// ������cash_physical
	CashSettle = 1,
	PhysicalSettle,



	// For callable bonds.
	NonCallableNonPutable = 0,//added by GL
	Callable = 1,
	Putable,

	// Volatility dynamics.
	//������VolMethodFlag/vol_method_flag/volMethod(convertible bond)
	//sticky ճ�Ե�
	StaticVol = 1,      // Static Vol Surface.
	StickyDelta,        // Vol Surface Moves With Spot -- Convolution.
	StickySkew,         // ATM-Vol From The Static Vol Surface, Skew Moves With Spot -- Sophis.

	//������divTreatmentFlag,ModelFlag
	// Model methods used by the PDE solver.
	DiscreteDiv = 1,    // Handle discrete dividends rigorously.
	ProportionalDiv,    // Turn discrete dividends into proportional dividends.
	ContinuousYield,    // Merge discrete dividends with repo and treat as continuous yield.

	// Boundary searching for PDE.
	UpLimit = 1,
	LowLimit,

	// PDE attached tail model.
	// ������m_tail_model
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
	//������which_model
	WorstOf = 1,
	BestOf, 
	OneTouchSum,

	//===��Դ��SingleStockBase.h
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
//inline�������������Ƶ�����ú�����ջ�ռ���������⡣
//�������Դ������͸���Ϊ���ۣ�����ʡȥ�˺������õĿ������Ӷ���ߺ�����ִ��Ч�ʡ����ִ�к������ڴ����ʱ�䣬����ں������õĿ����ϴ���ôЧ�ʵ��ջ����١�
//�������ڲ��ܳ���ѭ��

//ģ�庯�����巽ʽ��template <class T> T f(T a,T b){}
template <class T>T inline maxi(T a, T b) { return a > b ? a : b; }
template <class T>T inline mini(T a, T b) { return a < b ? a : b; }
template<class T>inline int signof(T& a) { if (a < 0) return(-1); return(1); }

//C++������洢�ļ��ַ�ʽ
//�������飺int a[40];��С�̶����ٶȿ�
//����ָ�룺 int *a; a = new int[40]; �����a���Եȼ����������飻����a����ʾ�����׸�Ԫ�صĵ�ַ��
//vector: #include<vector> vector<int> a(N); a.push_back(888); ʹ��new/delete�����ڴ���� ���ȿɱ䣬��Ч�ʵ�
//array: #include<array> array<int,2> a = {1,2}; ���ȹ̶�������ȫ�ӿڣ�Ч��ͬ�������顣
//valarray: #include<valarray> valarray<int> a(10); ������ֵ��������飻 ��ͨ��resize�ı��С��ע�������С�����ݽ���ʧ��shift/cshift���������ݵ�ƽ��
typedef valarray< double > Array1D; //ע�⣺Array1D x(0.5,10); x.resize(10,0.5); //��ʼ��ʱ��ǰ��Ϊvalue,����Ϊ������resizeʱ��ǰ��Ϊ����������Ϊvalue
typedef valarray< Array1D > Array2D;
typedef valarray< Array2D > Array3D;
typedef valarray< int > Array1I;
typedef valarray< Array1I > Array2I;
typedef valarray< long > Array1L;
typedef valarray< Array1L > Array2L;
typedef valarray<string> Array1S;
ostream& operator<<(ostream&, const Array1D&);
ostream& operator<<(ostream&, const Array2D&);

//����һЩ����Array2D�ĺ���=========
double dot(const Array1D& a1, const  Array1D& a2);//�������
Array2D dot(const Array2D& m1, const  Array2D& m2);//����˻�
Array2D dot_element(const Array2D& m1, double x);//�������Ծ����ÿһ��Ԫ��
Array1D dot(const Array2D& m1, const  Array1D& a1);//���������
Array1D dot_element(const Array1D& a1, const  Array1D& a2);//Ԫ�����
Array1D plus_element(const Array1D& a1, const  Array1D& a2);//Ԫ�����
Array2D plus_element(const Array2D& m1, const  Array2D& m2);//Ԫ�����
Array2D dot_element(const Array2D& m1, const  Array2D& m2);//Ԫ�����
Array2D trans(const Array2D& m);//��Array2Dת��
double trace_Array2D(const Array2D& m);//�Խ���Ԫ��֮��
Array1D minus_Array1D(const Array1D& first, const Array1D& second);//�������
double sum_Array1D(const Array1D& first);//����Ԫ�����
Array1D getPart_Array1D(Array1D& originalArr, size_t begIndex, size_t endIndex);//����[begIndex,endIndex]֮��������飬ע����python������:[begIndex,endIndex)
Array2D getPart_Array2D(Array2D& originalArr, size_t begIndex, size_t endIndex);
double getNorm2(Array1D&);//����2����
double maxDiag(Array2D&);//�Խ������Ԫ��




//2. ���峣�õ����ݽṹ

// ************************************************************************************
// Memory allocation & other common functions.
// ************************************************************************************


//2.1 �ɱ䳤��һά���ݽṹ
//tvec---�ɱ䳤�ȵ�����;ģ��
//dvec---�̳���tvec<double>
//ivec---�̳���tvec<int>
//cvec---�̳���tvec<char> ��append���ַ���              //������util.h��δ���壬��utils.h�ж��壻��excel.h���õ�cvec
//cvecv---�̳���tvec<cvec>  �ɱ䳤��һϵ���ַ������ɵ�����

//2.2 �ɱ䳤�Ķ�ά���ݽṹ
//imat---�ɱ�ߴ�Ķ�ά���飬���int����ֵ
//dmat---�ɱ�ߴ�Ķ�ά���飬���double����ֵ
//dmatv---Ӧ����һϵ��dmat���ɵ����飬����Ϊʲô�ö�άָ��

//�Զ���ɱ䳤����ĳ��ýӿ�
//1. ���캯������һ������n1��ʼ���������ٳ���Ϊn1�Ŀռ�
//2. ���캯������ͨ��Array1D,Array2D�ȹ���һά�ɱ䳤����
//3. resize(n0): �����ɱ䳤���鳤��Ϊn0��n0<n1���������(n1-n0)��ֵ;n0>n1����
//4. ��ʽת��operator: tvec������������ڲ�����p,ͨ��[],*��ȡp�ڲ���ֵ
//5. ���ƹ��캯����dvec a(b); ����b��һ���Ѿ����ڵ�dvec����
//6. operator=���أ�dvec a = b;



// Variable size vector.  Behaves as Type*.
template<class Type> class tvec {
	public:

		//=============================4�๹�캯��============================
		//1. Ĭ�Ϲ��캯��+�Զ��幹�캯����ϡ����ַ�ʽ�������1. tvec t0��2.tvec t0(5);
		//���ڸö��巽ʽ������Ĭ�Ϲ��캯�������Բ����ٶ���һ��Ĭ�Ϲ��캯����tvec ():n(0),p(new Type[0]){};
		tvec(size_t n1 = 0) : n(n1), p(new Type[n1]) {};
		//���캯����ʼ���б���ʼ���б�ĳ�Ա��ʼ��˳��:C++ ��ʼ�����Աʱ���ǰ���������˳���ʼ���ģ������ǰ��ճ����ڳ�ʼ���б��е�˳��
		// 
		//2. ���ƹ��캯��
		tvec(const tvec& v) : n(v.n), p(v.n > 0 ? new Type[v.n] : 0)
		{
			size_t	i;
			for (i = 0; i < v.n; i++) p[i] = v.p[i];
		}
		//3. ������=������
		tvec& operator=(const tvec& v)
		{
			size_t		i;
			resize(v.n);
			for (i = 0; i < v.n; i++) p[i] = v.p[i];
			return *this;
		}
		//============================��������================================
		~tvec(void) 
		{
			//printf("%f\n", p[0]);
			delete[] p; 
			//printf("delete tcev\n");
		}

		//============================�����Զ��庯��===========================

		//----------------------------f1:resize�ߴ磬�����ı�ԭֵ---------------
		void resize(size_t n0) {
			//������valarray�е�resize: 
			//valarray��resize���賤�ȣ��������³�ʼ����myarray.resize(3,1);����Ϊ3��1.û��1�Ļ���Ĭ��3��0. 
			//�����resize����ԭ�����е�ֵ������ȥ�����������㡣
			size_t		i;
			Type* p0 = new Type[n0]{};

			for (i = 0; i < (n < n0 ? n : n0); i++) p0[i] = (*this)[i];//������λ�õ�Ԫ�ػ������ڱ���λ��
			for (i = (n < n0 ? n : n0); i < n0; i++) p0[i] = 0.0;//������ȱ䳤����0��
			delete[] p;
			p = p0;
			n = n0;
		}

		//resize�ߴ磬�µ�ֵ��Ϊv0
		void resize(size_t n0, Type v0) {
			//������valarray�е�resize: 
			//valarray��resize���賤�ȣ��������³�ʼ����myarray.resize(3,1);����Ϊ3��1.û��1�Ļ���Ĭ��3��0. 
			//�����resize����ԭ�����е�ֵ������ȥ�����������㡣
			size_t		i;
			Type* p0 = new Type[n0];
			for (i = 0; i < (n < n0 ? n : n0); i++) p0[i] = v0;//������λ�õ�Ԫ�ػ������ڱ���λ��
			for (i = (n < n0 ? n : n0); i < n0; i++) p0[i] = v0;//������ȱ䳤����0��
			delete[] p;
			p = p0;
			n = n0;
		}

		//---------------------------f2����ʽת�����������תΪ�ڲ�������--------------------
		//operator��ʹ�÷���֮һ����ʽ����ת����operator casting; ��һ�ֳ����ô�Ϊ�����������ؼ�operator overloading
		//����Ҫ�ĵط�tvec������Ե�������ı���pʹ�ã���tvec a; a[0]����ȡ��p��ָ��������е�ֵ��
		inline operator Type* (void) const { return p; }	// Violate const.

		//----------------------------f3:push_back,����resize��Ĭ�����ֵ-------------------

		void push_back(Type v0)
		{
			resize(n + 1);//��������һ
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
			//order =1,-1���ֱ��ʾ���յ�����ݼ��ķ�ʽ�洢
			//repeat = true,false�ֱ��ʾ���Դ洢�ظ�ֵ���򲻿��Դ洢�ظ�ֵ.
			if (n == 0)push_back(v0);
			if (repeat == true || isContain(v0) == false)
			{
				if (order == 1)//Ĭ��ԭ�����ǰ��յ������е�
				{
					int k = -1;//��Ҫ�����λ��
					for (int i = 0; i < n; i++)if (v0 <= p[i]) { k = i; break; }

					if (k != -1)push(v0, static_cast<size_t>(k));
					else push_back(v0);
				}
				else//Ĭ��ԭ�����ǰ��յݼ����е�
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
			//order=1������order=-1�ݼ�
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
			//�ڵ�k��λ�õ�Ԫ���޳�
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
			//�ڵ�k��λ�ô����Ԫ��v0
			if (n == 0 || k >= n) push_back(v0);//���k������Ԫ�صĸ�������������������λ�ò���
			else if (k <= 0) push_first(v0);//���kΪ���������ڵ�һ��λ�ò���
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

		//==============================��Ա����==================================
		size_t		n;//����ĳ���
		Type*   p;//���鳤�ȵ��׵�ַ



	private:
};

// Variable size vector.  Behaves as double*.
class dvec : public tvec<double> {
public:
	//==================================���캯������===================
	//1.���಻�̳и���Ĺ��캯����
	//2.������๹�캯�����Σ����������ʽ���ø���Ĺ��캯�������÷�����ʾΪ":father(n1)". �����������캯����ʵ���˸��๹�캯���ĵ��á�
	
	//Ĭ�Ϲ��캯��
	dvec(size_t n1 = 0) : tvec<double>(n1) {};//A(b)ʵ��������������b��ʼ��A�ĳ�Աx;��x=b; �ǳ�ʼ���б�ʽ��
	dvec(size_t n1,double v0) : tvec<double>(static_cast<int>(MAX(n1,0))) {
		//printf("using copy constructor(Array1D)\n");
		for (int i = 0; i < MAX(n1, 0); i++) (*this)[i] = v0;
	}

	//copy���캯��������������ʹ�÷�ʽ
	// Array1D a0; dvec d0 = a0;����dvec d0(a0);
	dvec(const Array1D& a);//��Array1D����dvec
	dvec(const dvec& a);
	dvec(const initializer_list<double>& _Ilist)
	{
		//printf("using copy constructor(initializer_list)\n");
		n = static_cast<int>(_Ilist.size());
		resize(n);//����n���ȵĿռ�
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

	//������=�����أ���Array1D����ֵ���Ѿ����ڵ�dvec����
	dvec& operator=(const Array1D& a)
	{
		//printf("use operator overload(Array1D)\n");
		n = static_cast<int>(a.size());
		resize(n);
		for (int i = 0; i < n; i++)p[i] = a[i];
		return *this;
	}
	//������=�����أ���initializer_list����ֵ���Ѿ����ڵ�dvec����
	dvec& operator=(const initializer_list<double>& _Ilist)
	{
		//printf("use operator overload(initializer_list)\n");
		n = static_cast<int>(_Ilist.size());
		resize(n);//����n���ȵĿռ�
		int i = 0;
		for (auto iter = _Ilist.begin(); iter < _Ilist.end(); iter++) { p[i] = *iter; i++; }
		return *this;
	}

	dvec(const Array2D& a);//��Array2D����dvec
	//================================�����Զ��庯��===================
	//------------------------------f1:��dvec����ת��ΪArray1D����-----
	Array1D getArray1D()
	{
		Array1D a0(n);
		for (size_t i = 0; i < n; i++)a0[i] = p[i];
		return a0;
	}
	double sum();//���
private:
	//dvec(double);//���޶��壡��
};
ostream& operator<<(ostream&, const dvec&);

// Variable size vector.  Behaves as int*.
class ivec : public tvec<int> {
public:
	ivec(size_t n1 = 0) : tvec<int>(n1) {};
	ivec(const Array1I& a);
	ivec(const Array2I& a);//��Array2D����ivec
	Array1I& getArray1I()
	{
		Array1I a0(n);
		for (size_t i = 0; i < n; i++)a0[i] = p[i];
		return a0;
	}

private:
	//ivec(double);//���޶���
};

//Variable size Vector. ������ char*
//C++�洢�ַ����ļ��ַ�ʽ
// char str0[2] = {'a','b','\0'};
// char str1[] = "ab\0";//��������Ϊ���飬��ü���\0
// char *str2 = "ab"; //char * �� char []������char*�Ǳ�����ֵ���Ըı䣬 char[]�ǳ�����ֵ���ܸı�

//strlen, strcpy, strncpy������string.h�С�
//string.h, cstring, string �����������
//string.h�ļ���C���ԵĿ⣻cstring��C++��string.h�ļ����������װ;
//string����ǰ�������б��ʲ���ˡ�����C++�Լ�������װ���࣬ͬ�������ַ��������������õ��˺ܶ�Ĳ��������صȷ�����ʵ�ַ�����C��׼���е�string.h�кܴ���


//Variable size Vector. Behaves as char*. 
//���Ե���append����չԭ�ַ���
class cvec : public tvec<char> {
public:
	cvec(int n1 = 0) : tvec<char>(n1) {};
	//strlen,strcpy,strncpy������������string.h�У�����δ����string.hҲ����ʹ�ã��������������!?
	//strlen:�ó��Ľ������������\0;����Ҫ����1��
	//strcpy:�Ѻ���'\0'���������ַ������Ƶ���һ����ַ�ռ䣬����ֵ������Ϊchar*;ǰ����ΪĿ���ַ�������Ϊ������Դ��ַ��
	//strncpy: ����Դ�ַ���ǰn���ַ����Ƶ���һ����ַ�ռ䣬����ֵ������Ϊchar*;ǰ����ΪĿ���ַ�������Ϊ������Դ��ַ��
	cvec(const char* s) : tvec<char>(s ? static_cast<int>(strlen(s) + 1) : 0) { if (s) strcpy(p, s); };
	cvec(const char* s, int n) : tvec<char>(n + 1) { strncpy(p, s, n); p[n] = 0; };
	void append(const char* s); //�ú����Ǵ�utils.cpp�и��Ƶ�util.cpp��
};


// Vector of cvec:
class cvecv : public tvec<cvec> {
public:
	cvecv(int n2 = 0) : tvec<cvec>(n2) {};//���������ø���ĺ��ι��캯��
};
// ************************************************************************************

// Variable size matrix of integers
class imat {
public:
	//imat(int r1, int c1) : r(r1), c(c1), p(new int[r1 * c1]) {}
	//����������־���using operator"*" on a 4 byte value and then casting the value to a 8 byte value.
	//ԭ��int[]�з���ı�����size_t���ͣ�ռ��8 �ֽڣ� ������int�������int���ͣ�ռ��4���ֽڣ���4�ֽڱ����ŵ���Ӧ�÷�8�ֽڵ�λ�þͳ����˾��档

	imat(int r1, int c1) : r(r1), c(c1), p(new int[static_cast<long>(r1) * static_cast<long>(c1)]) {}//4�ֽ�ǿ��ת��Ϊ8�ֽ�
	//32λ��������int/float/unsigned int/long/unsigned long: 4�ֽڣ� long long/double��8�ֽ�
	//64λ������: int/float/unsigned int:4�ֽڣ� long/long long/unsigned long/double:8�ֽ�
	~imat(void) { delete[] p; }
	void resize(int r, int c);
	//const�޶��� ֻ�ܶ�ȡ�������޸ĳ�Ա����
	inline int* operator[](int r_) const { return p+ static_cast<long>(r_*c); }
	inline operator int* (void) const { return p; }	

	//��Ա�������У��У���ʼָ��
	int	r;
	int	c;	
	int* p;
private:
	//��������������Ϊ�Լ����壬֮ǰֻ��������δ���塣
	imat(const imat& d);//���ƹ���
	imat& operator=(const imat&);//operator=����������
};





// ************************************************************************************

// Variable size matrix
//����һ���ɱ�size�Ķ�άdouble����
//��������桢���Է��������ĺ���������Numerics.h/.cpp��
class dmat 
{
	public:

		dmat() : r(0), c(0), p(0) {}
		dmat(size_t r1, size_t c1) : r(r1), c(c1), p(new double[r1 * c1]) { init(); } //�ó��ȣ���ȹ���һ�����󡣳�Ա���������ð�ű�ʾ��ֵ
		dmat(const Array2D& a); //���Զ����valarray<valarray<double>>�����͹���dmat
		dmat(const dmat& d);
		dmat& operator=(const dmat&);

		~dmat(void) {
			//printf("delete dmat: %d,%d,%f,%04x\n",r,c,p[0],p);
			delete[] p; 
		}

		void resize(size_t r, size_t c); //�ɷŴ󣺷Ŵ�ʱ���㣻����С����Сʱά��ԭλ�ò���
		void transpose(void);//ת��

		//-----------2022-03-04��ӣ��������������--------------
		void init() { for (size_t i = 0; i < rows() * cols(); i++) p[i] = 0.0;  //printf("\n new: %d,%d,%d\n", p, r, c);
		}
		void set_default_values(double x) {
			for (size_t i = 0; i < rows() * cols(); i++) p[i] = x;  //printf("\n new: %d,%d,%d\n", p, r, c);
		}
		size_t size() const { return static_cast<size_t>(r * c); }
		bool null() { return (size() ? false : true); }
		double norm(int);//δ�������з���
		bool isSizeEqual(dmat& x);
		size_t rows() const { return r; }
		size_t cols() const { return c; }
		double maxDiag();
		double* pointer() const { return p; }
		Array1D row(size_t _r) const;//��ȡ��_r�е�ֵ, _r��0��r-1,���򱨴�
		Array1D col(size_t _c) const;//��ȡ��_c�е�ֵ, _c��0��c-1,���򱨴�
		double operator()(size_t _r, size_t _c); //������(1,1)ȡֵ
		const double operator()(size_t _r, size_t _c) const; //������(1,1)ȡֵ
		dmat& operator=(double dVal);//��������Ԫ�ظ���ֵ
		
		dmat& operator=(const Array2D&);
		bool operator==(const dmat& cThat) const;
		dmat& operator+=(dmat& x);//�����ӦԪ����+/-/*//��һ���������ӦԪ��
		dmat& operator-=(dmat& x);
		dmat& operator*=(dmat& x);
		dmat& operator/=(dmat& x);
		//-----------2022-03-04��ӣ��������������--------------

		inline double* operator[](int r_) const { return p +r_*c; }//����ͨ��mat[i][j] = 888.0������ֵ
		//����һ��ָ��double��ָ�룬ָ��Ӽ�����ʾ��������ƽ����ͬ������λ�ã�
		//(*this)[i][j] �״�ʹ��ƽ�Ƶ���i�п�ͷ�ĵ�һ��Ԫ��-->��*this��[i] ���ص��Ǹ�dmat�����е�����ָ��-->�ټ�[j]��ʾ����ָ�����ƽ��j��λ��
		//this[i][j]���Ӧ���Ƿ���ָ��ĳ���ض�Ԫ�ص�ָ�룬ȡֵ��Ӧ����*(this[i][j]),Ӧ����(*this)[i][j]�ȼ۰ɣ�������һ����ʽת������

		inline operator double* (void) const { return p; }	// Violate const.��ʽת�����������ת��Ϊ�ڲ���ָ�����p,�������ϵ�(*this)���ص���p
		size_t			r;
		size_t			c;	// Can't change this once data entered.
		double*         p;
	private:
		
		
};

//----------�������Ӧ����-----
dmat matrix_Product(dmat& left, dmat& right);//�������
dmat operator*(dmat& left, dmat& right);//�������
dmat dot_Product(dmat& left, dmat& right);//��ӦԪ�����
dmat operator-(dmat& left, dmat& right);//����Ԫ�����
dmat operator+(dmat& left, dmat& right);//����Ԫ�����
dmat operator/(dmat& left, dmat& right);//����Ԫ�����
dmat operator-(dmat& left, double x);//����Ԫ�ؼ�����
dmat operator*(double x,dmat& left);//����Ԫ�س����ض�ֵ
dmat transpose(dmat& x);//ת��
ostream& operator<<(ostream&, const dmat&);
//istream& operator>>(istream& is, dmat& tThis);
//----------�������Ӧ����-----




/* ��ED_Analytics.h�У�������MemoryAllocator.cpp�еĿ��ٶ�ά����ĳ��� */
//һ��û��Ҫ�ã�ֱ����dmat����󼴿ɡ�
double** New2DMatrix(long nrow, long ncol);
void Delete2DMatrix(double** m);




// Vector of matrices.
//��ʾ��һ��dmat�����������
class dmatV 
{
	public:
		dmatV(int n, const Array2D** mat = 0);
		~dmatV(void);
		inline operator const dmat** (void) const { return p; }
		int	n;//
	private:
		const dmat** p;//dmat���ɵ����飬����ֻҪһ��*�Ϳ�������
		//����dmat��������һ����ά����
		//dmat** p��ʾ����һ��ָ��һϵ��dmat�����ַ����ָ�룻pָ���ָ����ָ���dmat�������ڴ��в�һ������
		//dmat*p �����p��ʾdmat������׵�ַ����ô��Щdmat�������ڴ����������ġ�
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












