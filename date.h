// Dates.
#ifndef __date_h__
#define __date_h__

//#include <vector>
//#include "type.h" //用到了变量类型ANFPED_basis
#include"dataStructure.h" //在相应的cpp文件中用到了MAX，MIN函数
#include"QConstants.h"
#include<string>//处理日期字符串
#include<ctime>
//#include<iostream>
//using namespace std;

//=========================================QDate类中需要用到的常量或者函数===========================
#define EXCEL_OFFSET (2)
// Number of days in (feb 0, feb y].  y is years from start of a 400 year cycle.
#define DAYS(y)	( 365*(y) + (y)/4 - (y)/100 + (y)/400 )
#define ISLEAP(y)	( (y)%4==0 && ((y)%100!=0 || (y)%400==0) )// 在这里等价于( (y)%4==0 && (y)%100!=0） || (y)%400==0) 
// **********************************************************************
// Binary search in array[0...N-1] for target, returning index or -1 in result.
#define BSRCH(N,array,target,result) {\
	(result)=-1;\
	int	BSRCH_lo=0;\
	int	BSRCH_hi=(N)-1;\
	if ((array) && (N)>0 && (array)[BSRCH_lo]<=(target) && (target)<=(array)[BSRCH_hi]) {\
		for(int BSRCH_mid=BSRCH_hi; 1; BSRCH_mid=(BSRCH_lo+BSRCH_hi)/2) {\
			if ((target)==(array)[BSRCH_mid]) {\
				(result)=BSRCH_mid;\
				break;\
			}\
			if (BSRCH_mid<=BSRCH_lo) break;\
			if ((target)<(array)[BSRCH_mid]) BSRCH_hi=BSRCH_mid;\
			else BSRCH_lo=BSRCH_mid;\
		}\
	}\
}

static const int monthCum[] = { 0,31,61,92,122,153,184,214,245,275,306,337,366 };
static const int monthDay[] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };//每个月的天数



// ====================================QDateSpan - defines how dates are adjusted=================
//表示的是以后的产品中需要用的每个period长度，
//成员变量: 年数，月份数，天数，星期数，一般这些变量是互斥的。
//在基类QDateSpan中并未要求四个成员变量互斥(由QDate& operator+=(const QDateSpan& qThat);可以看出)，但是在继承类QFrequency中要求变量互斥，且m_lWeeks=0
class  QDateSpan
{
	public:
		QDateSpan(const QDateSpan&);
		QDateSpan(unsigned long  lMonths, unsigned long lYears, unsigned long lDays = 0, unsigned long lWeeks = 0);
		QDateSpan();

		unsigned long& Years() { return m_lYears; }
		const unsigned long Years() const { return m_lYears; }
		unsigned long& Months() { return m_lMonths; }
		const unsigned long  Months() const { return m_lMonths; }
		unsigned long& Days() { return m_lDays; }
		const unsigned long  Days() const { return m_lDays; }
		unsigned long& Weeks() { return m_lWeeks; }
		const unsigned long  Weeks() const { return m_lWeeks; }

		// Operators:
		const QDateSpan& operator=(const QDateSpan&);
		bool  operator==(const QDateSpan&)const;
		bool  operator!=(const QDateSpan& tThat) const { return !(*this == tThat); }
		QDateSpan& operator+=(const QDateSpan&);

	protected:
		unsigned long  m_lYears;
		unsigned long  m_lMonths;
		unsigned long  m_lDays;
		unsigned long  m_lWeeks;
};
ostream& operator<<(ostream&, const QDateSpan&);
istream& operator>>(istream&, QDateSpan&);


//=============================QSettlementCalc========================================
// 用于计算settlement 日期
//Contains flags needed to calculate a bond/equity settlement date.
//    At present three methods are catered for:
//      1. e_ActualDays:     Add m_nDaysToSettle days
//                           This method is best constructed thus:
//                               QSettlementCalc QSettlementCalc(nDayse_ActualDays);
//      2. e_BusinessDays:   Add m_nDaysToSettle business days
//                           This method is best constructed thus:
//                               QSettlementCalc QSettlementCalc(nDays);
//      3. e_NextEndOfMonth: Use the last business day of the month 
//                           (or of the next month if this is too close)
//                           This method is best constructed thus:
//                               QSettlementCalc QSettlementCalc(e_NextEndOfMonth);

class  QSettlementCalc
{
	public:
		//Constructors
		QSettlementCalc();
		QSettlementCalc(int nDaysToSettle,
			ESettlementCalcType     eSettlementCalcType = ESettlementCalcType::e_BusinessDays,
			EAdjustConvention       eAdjustConvention = EAdjustConvention::e_Following);

		QSettlementCalc(const QSettlementCalc& qThat) { *this = qThat; }

		//Operators
		QSettlementCalc& operator=(const QSettlementCalc& QSettlementCalc);
		bool operator==(const QSettlementCalc& QSettlementCalc) const;

		int& DaysToSettle() { return m_nDaysToSettle; }
		const int  DaysToSettle() const { return m_nDaysToSettle; }
		ESettlementCalcType& SettlementCalcType() { return m_eSettlementCalcType; }
		const ESettlementCalcType  SettlementCalcType() const { return m_eSettlementCalcType; }
		EAdjustConvention& AdjustConvention() { return m_eAdjustConvention; }
		const EAdjustConvention& AdjustConvention() const { return m_eAdjustConvention; }

	private:
		int                 m_nDaysToSettle;
		//CCityCodeMask    m_cCityCodeMask;
		ESettlementCalcType m_eSettlementCalcType;
		EAdjustConvention   m_eAdjustConvention;
};

 ostream& operator<<(ostream&, const QSettlementCalc&);
 istream& operator>>(istream&, QSettlementCalc&);




// ======================================================Frequency class===========================================
// Years, Months, Weeks, Days are mutually exclusive互斥
// QFreuency与EFrequency的关系？
// 1. 可以用EFrequency变量构成QFrequency
// 2. QFrequency对象可以隐式转换为EFrequency变量
//-------------------------------------------------------------------------------
 class QFrequency : public QDateSpan
 {
	 public:
		 QFrequency(EFrequency = EFrequency::e_SemiAnnually);
		 QFrequency(unsigned int nDays, unsigned int nMonths, unsigned int nYears):QDateSpan(nMonths, nYears, nDays){}//三变量中有且仅有一个为非0值，用于表示每个periods的时间长度
		 QFrequency(const char*);
		 // Cast to double returns the number of periods / year
		 operator double() const;//返回一年划分为几个periods
		 // The inverse of the char * constructor above
		 operator string () const;//operator用于隐式类型转换
		 operator EFrequency () const;//operator用于隐式类型转换,将类对象隐式转化为EFrequency，比如m_lMonths==1, 自动转换为EFrequency::e_Monthly
		 bool IsMonthly() const { return (m_lMonths == 1); }
		 bool IsQuarterly() const { return (m_lMonths == 3); }
		 string shortString() const;
		 static string stringFromMonths(int months);
 };





// day count convention:计算利息时，两个日期之间的天数，以及一年的总天数

class QDate;
typedef valarray< QDate > ArrayDate1;
typedef valarray< ArrayDate1 > ArrayDate2;
class QDate
{
	//类名定义为QDate，使之与其他名称区分
	//构建QDate的原则是：尽量不改变原来的函数，因为原来的函数经过了较好的测试
public:
	//====================================================构造函数=========================================
	//默认构造
	QDate() :year(1900), month(1), day(1), ExcelDay(1) { m_count++; }//默认构造函数，若未定义，在ArrayDate中使用时，刚开始未初始化，会出错。
	QDate(int _year, int _month, int _day); //用年、月、日初始化
	QDate(int _ExcelDay);//用一个整数初始化,将excel整数日期(1900-01-01定义为整数1)日期转化为年、月、日
	//用字符串构造
	QDate(const std::string datestr);
	//复制构造
	QDate(const QDate& obj);
	
	//====================================================析构函数=========================================
	~QDate(void);

	//===============================================获取日期的年月日==========================================
	int getExcelDay() const { return ExcelDay; }//定义常成员函数，该成员函数不能用来改变成员变量的值；
	int Year() const { return year; }
	int Month() const { return month; }
	int Week() const { return (ExcelDay - 2) % 7 + 1; }//返回当前日期为星期几,分别为1，2,......,6,7
	int Day() const { return day; }
	
	int EndOfMonth();//返回当前日期所在月份的最后一天
	int EndOfMonth() const;

	//============================================日期加减操作符重载================================
	QDate operator+(const int days); //注意+与=的区别：+是内部创建的变量，最好不要返回其引用；=返回其自身，本身就是外部创建的，所以返回引用。
	QDate operator-(const int days);
	QDate& operator=(const QDate& qd0);
	QDate& operator=(int i0);
	QDate& operator++(); //注意++用在变量前面和后面需要定义不同的重载，这个是prefix
	QDate& operator--(); //参考：https://stackoverflow.com/questions/49711535/c2676-binary-does-not-define-this-operator
	QDate operator++(int) { return QDate(ExcelDay++); } // postfix
	QDate operator--(int) { return QDate(ExcelDay--); } // postfix

	//double operator-(const QDate& tThat) const { return (ExcelDay - tThat.getExcelDay()); }//两个日期相减
	bool operator < (const QDate& qd0) const;
	bool operator > (const QDate& qd0) const;
	bool operator <= (const QDate& qd0) const;
	bool operator >= (const QDate& qd0) const;
	bool operator == (const QDate& qd0) const;
	bool operator != (const QDate& qd0) const;
	operator double() const { return ExcelDay; }//再某个函数需要double类型变量时，可以用放入QDate变量
	//------------------与QDateSpan的函数
	QDate& operator+=(const QDateSpan& qThat);//这里的形参是基类的引用，却可以传递QFrequency对象。也就是继承类可以直接赋值给基类
	QDate& operator-=(const QDateSpan& qThat);
	
	//=================================在当前的日期上加上固定的天数？星期数？月份数？年数？（考虑调整工作日）=======================
	//d1 = d0.AddPeriod(); d0的值不被改变
	QDate AddPeriod(int step, char unit, bool biz_day_adjust) const;
	QDate MinusPeriod(int step, char unit, bool biz_day_adjust) const;

	//=================================在当前的日期上加上固定的天数，星期数，月份数，年数（未考虑所加日期是否为工作日）===============
	//d0.AddDays(); d0自身的值被改变了
	void AddDays(int days);
	void AddWeeks(int weeks);
	void AddMonths(int months);//如果+n个月份数后，超过那个月的天数，则取那个月最后一天。
	
	void MinusMonths(int months);
	void AddYears(int years);
	double AddYears(double dYears, EAccrualBasis eAccrualBasis, bool bTruncateDay);
	double AddYears(double dYears, bool bTruncateDay);
	void MinusYears(int years);

	//注意以下若干个函数，会改变自身日期的值，并返回调整的天数；
	//AdjustToBusiness与FBD_int等8个函数比较起来的区别是，FBD_int8个函数并不改变自身的日期，这一点要特别注意
	int AdjustToStartOfMonth();//将当前日期调整为当月第一天，并返回调整的天数
	int AdjustToEndOfMonth();//将当前日期调整到当月最后一天，并返回调整的天数
	int AdjustToBusiness(EAdjustConvention eAdjustConvention = EAdjustConvention::e_ModifiedFollowing);//根据convention,将当前日期调整为最近的business day,改变自身日期，并返回调整天数
	int AddBusinessDays(int nBusinessDays);
	QDate SettlementDate(const QSettlementCalc& qSettlementCalc) const;


	QDate& operator+=(double dDays); //在自身的基础上加上特定的天数，改变自身. 本质上同AddDays
	QDate& operator-=(double dDays); //在自身的基础上加上特定的天数，改变自身

	//================================将QDate类型转化为string类型==============================================================
	//以下返回得日期得字符串形如"20230631"，共8位；
	string dateToString();//将date转为string类型
	string dateToString() const; //将date转为string类型

	string dateToString(int String_type);//将date转为string类型
	string dateToString(int String_type) const; //将date转为string类型



	


	//================================节假日，工作日; 上/下一个工作日; 第几个星期几=======================================================
	bool isHoliday() const;//判断当前是否为节假日
	bool isBusinessDay() const;//判断是否为工作日
	bool IsBetween(QDate date1, QDate date2) const;//判断当前日期是否在[date1,date2]之间
	bool isWeekend() const;
	bool isleap();//闰年与否？
	bool isleap() const;//闰年与否？
	bool IsMonthEnd() const;//判断当前是否为月末

	//---------------特别注意：以下business day调整，均不改变自身日期本身--------------------
	//MFBD:modified following business day;  FBD:following business day; PBD: previous business day; MPBD:modified previous business day
	//----如果当前日期为工作日，就返回当前日期；否则往后找下一个工作日
	int FBD_int();     //获得下一个bussiness date(int类型)===============同QDate中的Following
	QDate FBD_date(); //获得下一个bussiness date(QDate类型)
	//----如果当前日期为工作日，就返回当前日期；否则往前找下一个工作日
	int PBD_int();//同QDate中的Preceding
	QDate PBD_date();
	//----如果当前日期为工作日，就返回当前日期；否则往后找下一个工作日；如果该工作日在当月则返回；否则寻找原日期的前一个工作日
	int MFBD_int();//当前日期的mf,考虑周末,节日
	QDate MFBD_date();//当前日期的mf,考虑周末,节日
	//----如果当前日期为工作日，就返回当前日期；否则往前找上一个工作日；如果该工作日在当月则返回；否则寻找原日期的后一个工作日
	int MPBD_int();//当前日期的mf,考虑周末,节日
	QDate MPBD_date();//当前日期的mf,考虑周末,节日

	QDate NthDayOfWeekInMonth(unsigned Nth, unsigned weekday) const;//返回当前日期所在月的，第几个星期几；如果China Option交割日为第四个星期三
	QDate GetIMMDate(int nIMMDateNum=1, const QFrequency& qFrequency = EFrequency::e_Quarterly, unsigned nDayOfWeek=3, bool bNext=true) const;//IMM日期是指：3，6，9，12月的第三个星期三，常用于EuroDollar and Foreign Exchange期货期权的到期日
	//nIMMDateNum表示相对于当前日期的第几个IMM日期；
	//QFrequency表示月还是季度的第三个周三，一般是季度
	//nDayOfWeek表示the day of week,1表示星期一，2表示星期二，依次类推
	//bNext表示当前日期往前还是当前日期往后的IMM日期。特别注意：如果当前日期本身为IMMdate,往前算nIMMDateNum=1时，不包含自身；往后算nIMMDateNum=1时，是自己。
	int AdjustToImm(const QFrequency& qFrequency = EFrequency::e_Quarterly, bool bNext = true, unsigned nDayOfWeek = 3, int nIMMDateNum = 1);

	//---与下面的Accrual函数是一个作用，就是计算两个日期间的年化，这里的YearFraction来源与DllLibrary; 下面的Accrual用于RMI中的计算
	static double      YearFraction(const QDate& tDate1, const QDate& tDate2, EAccrualBasis = EAccrualBasis::e_30360);
	static double      YearFraction(const QDate& tDate1, const QDate& tDate2, EAccrualBasis eAccrualBasis, EFrequency eFreq);
	static bool        SpansLeapDay(const QDate& tDate1, const QDate& tDate2);//两个日期之间是否包含****-02-29这个日期
	static bool        SpansLeapYear(const QDate& tStartDate, const QDate& tEndDate);//两个日期之间是否跨越了闰年，闰年365天。
	static bool        leapYear(unsigned year);//判断某一年是否为闰年，与某对象无关。下面的isleap是判断该对象所在年份是否为闰年
	static unsigned    daysInYear(unsigned nYear);//一年的天数，366或者365
	static unsigned    daysInMonthYear(unsigned nMonth, unsigned nYear);//哪一年的哪一个月有几天
	static double      BasisDaysBetween(const QDate& tDate1, const QDate& tDate2, EAccrualBasis = EAccrualBasis:: e_30360);//两个日期间间隔的天数
	static int         BasisDaysInYear(EAccrualBasis, int nYear);
	static bool        IsBetween(const QDate& tDateIn, const QDate& tDate1, const QDate& tDate2);
	static int		   BusinessDaysBetween(const QDate& tStartDate, const QDate& tEndDate);
	static  QDate today()// return today's date.
	{
		// 基于当前系统的当前日期/时间
		time_t now = time(0);

		//cout << "1970 到目前经过秒数:" << now << endl;

		tm* ltm = localtime(&now);
		return QDate(1900 + ltm->tm_year, ltm->tm_mon + 1, ltm->tm_mday);

		// 输出 tm 结构的各个组成部分
		//cout << "年: " << 1900 + ltm->tm_year << endl;
		//cout << "月: " << 1 + ltm->tm_mon << endl;
		//cout << "日: " << ltm->tm_mday << endl;
		//cout << "时间: " << ltm->tm_hour << ":";
		//cout << ltm->tm_min << ":";
		//cout << ltm->tm_sec << endl;

	}







	//===================================其他相关函数==================================================================
	int EndAddMonths(int months);//+n个月份后，对应月份的最后一天
	int AddWorkdays(int days);//当前日期的基础上+days个工作日，中间不包含holidays; 返回最终对应日期
	int getNumofMEs(int begDate, int endDate);//两个日期之间有几个月末(包括首尾日期)
	int getNumofMEs(int endDate);
	int DaysOfYear();

private:
	int year, month, day;
	int ExcelDay;
	//所有的QDate公用相同的假期
	static int* hols;
	static size_t  n_of_hols;
	static size_t m_count;
	static void set_hols();//返回内部类对象指针的函数
};

//用于日期的输入输出
ostream& operator<<(ostream&, const QDate&);
istream& operator>>(istream& is, QDate& tThis);
//eg: 	QDate q1(2021, 1, 1);  cin >> q1; cout << q1 << "\n" << endl;
QDate plusSpan(const QDate& tThis, const QDateSpan& tThat);
//QDate operator+(const QDate& tThis, double dOffset);
QDate minusSpan(const QDate& tThis, const QDateSpan& tThat);

//==================================QDate类之外自己定义的相关函数=====================================
Array1I BinarySearch(const QDate& qd0, const ArrayDate1& date_vector, int starting_position);
Array1I BinarySearch(const QDate& qd0, const tvec<QDate>& date_vector, int starting_position);
double Accrual(int	date1, int	date2, quantEnum	basis);//返回day_factor=number_of_days/base,也就是两个日期间的年化数
double Accrual(const QDate& date1, const QDate& date2, quantEnum	basis);
ArrayDate1 DateVectorBuilder(const QDate& one_date, const QDate& another_date, quantEnum frequency, bool biz_day_adjust);//构建间隔一定周期的日期数组，数组包括首末两个日期
ArrayDate1 biz_day_between(const QDate& one_date, const QDate& another_date);



//==================================库中原有的相关函数=================================================
//两个日期间的年份数：relativedelta.relativedelta(maturity_date, current_day).years;
int deltaYears(QDate& d1, QDate& d2);//d1-d2的年份数,3.5年算3年，超过一整年才算一年
int deltaMonths(QDate& d1, QDate& d2);//d1-d2的月份数,3.5个月算3个月，超过一整月才算一月；不考虑年份，只比较月份
int lastDayInMonth(QDate& d);//每个月份的最后一天

// Convert excel day number to YMD.
void Day2YMD(int day, int* y, int* m, int* d);
// Convert YMD to excel day number
int YMD2Day(int y, int m, int d);
// Add months to date.
int addMonth(int date, int months);
int addYear(int date, int dy);
//是否未节假日
int isHol(int dt, int n, const int* hol);
int accrued_30(int date1, int date2, int Eflag);
// Get EndOfMonth date from months added to date.
int monthEnd(int date, int months);
//void GetNumMonthEnds(int sDate, int eDate, int& nMonths, vector<int>& MonthDates);
void GetNumMonthEnds(int sDate, int eDate, int& nMonths);
// Use Modified Following rule to find corresponding business day,
int MFBD(int date, int nHol, const int* hol);
int MFBD(int date);
int MPBD(int date, int nHol, const int* hol);
// Validate holidays.
//const char *holsOK(
//	int				n1,		// Number of holidys.
//	const int		*hol);	// Vector of holiday dates.

// Add working days to date, avoiding holidays.
// Assumes holidays are in ascending order with no duplicates (use holsOK to check).
int workDay(
	int				date,
	int				days,	// Number of days to add to date.
	int				n1,		// Number of holidys.
	const int* hol);	// Vector of holiday dates.

// Return accrued_days/days_per_year between two dates, according to rule.
#endif //__date_h__


