// Dates.
#ifndef __date_h__
#define __date_h__

//#include <vector>
//#include "type.h" //�õ��˱�������ANFPED_basis
#include"dataStructure.h" //����Ӧ��cpp�ļ����õ���MAX��MIN����
#include"QConstants.h"
#include<string>//���������ַ���
#include<ctime>
//#include<iostream>
//using namespace std;

//=========================================QDate������Ҫ�õ��ĳ������ߺ���===========================
#define EXCEL_OFFSET (2)
// Number of days in (feb 0, feb y].  y is years from start of a 400 year cycle.
#define DAYS(y)	( 365*(y) + (y)/4 - (y)/100 + (y)/400 )
#define ISLEAP(y)	( (y)%4==0 && ((y)%100!=0 || (y)%400==0) )// ������ȼ���( (y)%4==0 && (y)%100!=0�� || (y)%400==0) 
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
static const int monthDay[] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };//ÿ���µ�����



// ====================================QDateSpan - defines how dates are adjusted=================
//��ʾ�����Ժ�Ĳ�Ʒ����Ҫ�õ�ÿ��period���ȣ�
//��Ա����: �������·�������������������һ����Щ�����ǻ���ġ�
//�ڻ���QDateSpan�в�δҪ���ĸ���Ա��������(��QDate& operator+=(const QDateSpan& qThat);���Կ���)�������ڼ̳���QFrequency��Ҫ��������⣬��m_lWeeks=0
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
// ���ڼ���settlement ����
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
// Years, Months, Weeks, Days are mutually exclusive����
// QFreuency��EFrequency�Ĺ�ϵ��
// 1. ������EFrequency��������QFrequency
// 2. QFrequency���������ʽת��ΪEFrequency����
//-------------------------------------------------------------------------------
 class QFrequency : public QDateSpan
 {
	 public:
		 QFrequency(EFrequency = EFrequency::e_SemiAnnually);
		 QFrequency(unsigned int nDays, unsigned int nMonths, unsigned int nYears):QDateSpan(nMonths, nYears, nDays){}//�����������ҽ���һ��Ϊ��0ֵ�����ڱ�ʾÿ��periods��ʱ�䳤��
		 QFrequency(const char*);
		 // Cast to double returns the number of periods / year
		 operator double() const;//����һ�껮��Ϊ����periods
		 // The inverse of the char * constructor above
		 operator string () const;//operator������ʽ����ת��
		 operator EFrequency () const;//operator������ʽ����ת��,���������ʽת��ΪEFrequency������m_lMonths==1, �Զ�ת��ΪEFrequency::e_Monthly
		 bool IsMonthly() const { return (m_lMonths == 1); }
		 bool IsQuarterly() const { return (m_lMonths == 3); }
		 string shortString() const;
		 static string stringFromMonths(int months);
 };





// day count convention:������Ϣʱ����������֮����������Լ�һ���������

class QDate;
typedef valarray< QDate > ArrayDate1;
typedef valarray< ArrayDate1 > ArrayDate2;
class QDate
{
	//��������ΪQDate��ʹ֮��������������
	//����QDate��ԭ���ǣ��������ı�ԭ���ĺ�������Ϊԭ���ĺ��������˽ϺõĲ���
public:
	//====================================================���캯��=========================================
	//Ĭ�Ϲ���
	QDate() :year(1900), month(1), day(1), ExcelDay(1) { m_count++; }//Ĭ�Ϲ��캯������δ���壬��ArrayDate��ʹ��ʱ���տ�ʼδ��ʼ���������
	QDate(int _year, int _month, int _day); //���ꡢ�¡��ճ�ʼ��
	QDate(int _ExcelDay);//��һ��������ʼ��,��excel��������(1900-01-01����Ϊ����1)����ת��Ϊ�ꡢ�¡���
	//���ַ�������
	QDate(const std::string datestr);
	//���ƹ���
	QDate(const QDate& obj);
	
	//====================================================��������=========================================
	~QDate(void);

	//===============================================��ȡ���ڵ�������==========================================
	int getExcelDay() const { return ExcelDay; }//���峣��Ա�������ó�Ա�������������ı��Ա������ֵ��
	int Year() const { return year; }
	int Month() const { return month; }
	int Week() const { return (ExcelDay - 2) % 7 + 1; }//���ص�ǰ����Ϊ���ڼ�,�ֱ�Ϊ1��2,......,6,7
	int Day() const { return day; }
	
	int EndOfMonth();//���ص�ǰ���������·ݵ����һ��
	int EndOfMonth() const;

	//============================================���ڼӼ�����������================================
	QDate operator+(const int days); //ע��+��=������+���ڲ������ı�������ò�Ҫ���������ã�=������������������ⲿ�����ģ����Է������á�
	QDate operator-(const int days);
	QDate& operator=(const QDate& qd0);
	QDate& operator=(int i0);
	QDate& operator++(); //ע��++���ڱ���ǰ��ͺ�����Ҫ���岻ͬ�����أ������prefix
	QDate& operator--(); //�ο���https://stackoverflow.com/questions/49711535/c2676-binary-does-not-define-this-operator
	QDate operator++(int) { return QDate(ExcelDay++); } // postfix
	QDate operator--(int) { return QDate(ExcelDay--); } // postfix

	//double operator-(const QDate& tThat) const { return (ExcelDay - tThat.getExcelDay()); }//�����������
	bool operator < (const QDate& qd0) const;
	bool operator > (const QDate& qd0) const;
	bool operator <= (const QDate& qd0) const;
	bool operator >= (const QDate& qd0) const;
	bool operator == (const QDate& qd0) const;
	bool operator != (const QDate& qd0) const;
	operator double() const { return ExcelDay; }//��ĳ��������Ҫdouble���ͱ���ʱ�������÷���QDate����
	//------------------��QDateSpan�ĺ���
	QDate& operator+=(const QDateSpan& qThat);//������β��ǻ�������ã�ȴ���Դ���QFrequency����Ҳ���Ǽ̳������ֱ�Ӹ�ֵ������
	QDate& operator-=(const QDateSpan& qThat);
	
	//=================================�ڵ�ǰ�������ϼ��Ϲ̶������������������·����������������ǵ��������գ�=======================
	//d1 = d0.AddPeriod(); d0��ֵ�����ı�
	QDate AddPeriod(int step, char unit, bool biz_day_adjust) const;
	QDate MinusPeriod(int step, char unit, bool biz_day_adjust) const;

	//=================================�ڵ�ǰ�������ϼ��Ϲ̶������������������·�����������δ�������������Ƿ�Ϊ�����գ�===============
	//d0.AddDays(); d0�����ֵ���ı���
	void AddDays(int days);
	void AddWeeks(int weeks);
	void AddMonths(int months);//���+n���·����󣬳����Ǹ��µ���������ȡ�Ǹ������һ�졣
	
	void MinusMonths(int months);
	void AddYears(int years);
	double AddYears(double dYears, EAccrualBasis eAccrualBasis, bool bTruncateDay);
	double AddYears(double dYears, bool bTruncateDay);
	void MinusYears(int years);

	//ע���������ɸ���������ı��������ڵ�ֵ�������ص�����������
	//AdjustToBusiness��FBD_int��8�������Ƚ������������ǣ�FBD_int8�����������ı���������ڣ���һ��Ҫ�ر�ע��
	int AdjustToStartOfMonth();//����ǰ���ڵ���Ϊ���µ�һ�죬�����ص���������
	int AdjustToEndOfMonth();//����ǰ���ڵ������������һ�죬�����ص���������
	int AdjustToBusiness(EAdjustConvention eAdjustConvention = EAdjustConvention::e_ModifiedFollowing);//����convention,����ǰ���ڵ���Ϊ�����business day,�ı��������ڣ������ص�������
	int AddBusinessDays(int nBusinessDays);
	QDate SettlementDate(const QSettlementCalc& qSettlementCalc) const;


	QDate& operator+=(double dDays); //������Ļ����ϼ����ض����������ı�����. ������ͬAddDays
	QDate& operator-=(double dDays); //������Ļ����ϼ����ض����������ı�����

	//================================��QDate����ת��Ϊstring����==============================================================
	//���·��ص����ڵ��ַ�������"20230631"����8λ��
	string dateToString();//��dateתΪstring����
	string dateToString() const; //��dateתΪstring����

	string dateToString(int String_type);//��dateתΪstring����
	string dateToString(int String_type) const; //��dateתΪstring����



	


	//================================�ڼ��գ�������; ��/��һ��������; �ڼ������ڼ�=======================================================
	bool isHoliday() const;//�жϵ�ǰ�Ƿ�Ϊ�ڼ���
	bool isBusinessDay() const;//�ж��Ƿ�Ϊ������
	bool IsBetween(QDate date1, QDate date2) const;//�жϵ�ǰ�����Ƿ���[date1,date2]֮��
	bool isWeekend() const;
	bool isleap();//�������
	bool isleap() const;//�������
	bool IsMonthEnd() const;//�жϵ�ǰ�Ƿ�Ϊ��ĩ

	//---------------�ر�ע�⣺����business day�����������ı��������ڱ���--------------------
	//MFBD:modified following business day;  FBD:following business day; PBD: previous business day; MPBD:modified previous business day
	//----�����ǰ����Ϊ�����գ��ͷ��ص�ǰ���ڣ�������������һ��������
	int FBD_int();     //�����һ��bussiness date(int����)===============ͬQDate�е�Following
	QDate FBD_date(); //�����һ��bussiness date(QDate����)
	//----�����ǰ����Ϊ�����գ��ͷ��ص�ǰ���ڣ�������ǰ����һ��������
	int PBD_int();//ͬQDate�е�Preceding
	QDate PBD_date();
	//----�����ǰ����Ϊ�����գ��ͷ��ص�ǰ���ڣ�������������һ�������գ�����ù������ڵ����򷵻أ�����Ѱ��ԭ���ڵ�ǰһ��������
	int MFBD_int();//��ǰ���ڵ�mf,������ĩ,����
	QDate MFBD_date();//��ǰ���ڵ�mf,������ĩ,����
	//----�����ǰ����Ϊ�����գ��ͷ��ص�ǰ���ڣ�������ǰ����һ�������գ�����ù������ڵ����򷵻أ�����Ѱ��ԭ���ڵĺ�һ��������
	int MPBD_int();//��ǰ���ڵ�mf,������ĩ,����
	QDate MPBD_date();//��ǰ���ڵ�mf,������ĩ,����

	QDate NthDayOfWeekInMonth(unsigned Nth, unsigned weekday) const;//���ص�ǰ���������µģ��ڼ������ڼ������China Option������Ϊ���ĸ�������
	QDate GetIMMDate(int nIMMDateNum=1, const QFrequency& qFrequency = EFrequency::e_Quarterly, unsigned nDayOfWeek=3, bool bNext=true) const;//IMM������ָ��3��6��9��12�µĵ�������������������EuroDollar and Foreign Exchange�ڻ���Ȩ�ĵ�����
	//nIMMDateNum��ʾ����ڵ�ǰ���ڵĵڼ���IMM���ڣ�
	//QFrequency��ʾ�»��Ǽ��ȵĵ�����������һ���Ǽ���
	//nDayOfWeek��ʾthe day of week,1��ʾ����һ��2��ʾ���ڶ�����������
	//bNext��ʾ��ǰ������ǰ���ǵ�ǰ���������IMM���ڡ��ر�ע�⣺�����ǰ���ڱ���ΪIMMdate,��ǰ��nIMMDateNum=1ʱ������������������nIMMDateNum=1ʱ�����Լ���
	int AdjustToImm(const QFrequency& qFrequency = EFrequency::e_Quarterly, bool bNext = true, unsigned nDayOfWeek = 3, int nIMMDateNum = 1);

	//---�������Accrual������һ�����ã����Ǽ����������ڼ���껯�������YearFraction��Դ��DllLibrary; �����Accrual����RMI�еļ���
	static double      YearFraction(const QDate& tDate1, const QDate& tDate2, EAccrualBasis = EAccrualBasis::e_30360);
	static double      YearFraction(const QDate& tDate1, const QDate& tDate2, EAccrualBasis eAccrualBasis, EFrequency eFreq);
	static bool        SpansLeapDay(const QDate& tDate1, const QDate& tDate2);//��������֮���Ƿ����****-02-29�������
	static bool        SpansLeapYear(const QDate& tStartDate, const QDate& tEndDate);//��������֮���Ƿ��Խ�����꣬����365�졣
	static bool        leapYear(unsigned year);//�ж�ĳһ���Ƿ�Ϊ���꣬��ĳ�����޹ء������isleap���жϸö�����������Ƿ�Ϊ����
	static unsigned    daysInYear(unsigned nYear);//һ���������366����365
	static unsigned    daysInMonthYear(unsigned nMonth, unsigned nYear);//��һ�����һ�����м���
	static double      BasisDaysBetween(const QDate& tDate1, const QDate& tDate2, EAccrualBasis = EAccrualBasis:: e_30360);//�������ڼ���������
	static int         BasisDaysInYear(EAccrualBasis, int nYear);
	static bool        IsBetween(const QDate& tDateIn, const QDate& tDate1, const QDate& tDate2);
	static int		   BusinessDaysBetween(const QDate& tStartDate, const QDate& tEndDate);
	static  QDate today()// return today's date.
	{
		// ���ڵ�ǰϵͳ�ĵ�ǰ����/ʱ��
		time_t now = time(0);

		//cout << "1970 ��Ŀǰ��������:" << now << endl;

		tm* ltm = localtime(&now);
		return QDate(1900 + ltm->tm_year, ltm->tm_mon + 1, ltm->tm_mday);

		// ��� tm �ṹ�ĸ�����ɲ���
		//cout << "��: " << 1900 + ltm->tm_year << endl;
		//cout << "��: " << 1 + ltm->tm_mon << endl;
		//cout << "��: " << ltm->tm_mday << endl;
		//cout << "ʱ��: " << ltm->tm_hour << ":";
		//cout << ltm->tm_min << ":";
		//cout << ltm->tm_sec << endl;

	}







	//===================================������غ���==================================================================
	int EndAddMonths(int months);//+n���·ݺ󣬶�Ӧ�·ݵ����һ��
	int AddWorkdays(int days);//��ǰ���ڵĻ�����+days�������գ��м䲻����holidays; �������ն�Ӧ����
	int getNumofMEs(int begDate, int endDate);//��������֮���м�����ĩ(������β����)
	int getNumofMEs(int endDate);
	int DaysOfYear();

private:
	int year, month, day;
	int ExcelDay;
	//���е�QDate������ͬ�ļ���
	static int* hols;
	static size_t  n_of_hols;
	static size_t m_count;
	static void set_hols();//�����ڲ������ָ��ĺ���
};

//�������ڵ��������
ostream& operator<<(ostream&, const QDate&);
istream& operator>>(istream& is, QDate& tThis);
//eg: 	QDate q1(2021, 1, 1);  cin >> q1; cout << q1 << "\n" << endl;
QDate plusSpan(const QDate& tThis, const QDateSpan& tThat);
//QDate operator+(const QDate& tThis, double dOffset);
QDate minusSpan(const QDate& tThis, const QDateSpan& tThat);

//==================================QDate��֮���Լ��������غ���=====================================
Array1I BinarySearch(const QDate& qd0, const ArrayDate1& date_vector, int starting_position);
Array1I BinarySearch(const QDate& qd0, const tvec<QDate>& date_vector, int starting_position);
double Accrual(int	date1, int	date2, quantEnum	basis);//����day_factor=number_of_days/base,Ҳ�����������ڼ���껯��
double Accrual(const QDate& date1, const QDate& date2, quantEnum	basis);
ArrayDate1 DateVectorBuilder(const QDate& one_date, const QDate& another_date, quantEnum frequency, bool biz_day_adjust);//�������һ�����ڵ��������飬���������ĩ��������
ArrayDate1 biz_day_between(const QDate& one_date, const QDate& another_date);



//==================================����ԭ�е���غ���=================================================
//�������ڼ���������relativedelta.relativedelta(maturity_date, current_day).years;
int deltaYears(QDate& d1, QDate& d2);//d1-d2�������,3.5����3�꣬����һ�������һ��
int deltaMonths(QDate& d1, QDate& d2);//d1-d2���·���,3.5������3���£�����һ���²���һ�£���������ݣ�ֻ�Ƚ��·�
int lastDayInMonth(QDate& d);//ÿ���·ݵ����һ��

// Convert excel day number to YMD.
void Day2YMD(int day, int* y, int* m, int* d);
// Convert YMD to excel day number
int YMD2Day(int y, int m, int d);
// Add months to date.
int addMonth(int date, int months);
int addYear(int date, int dy);
//�Ƿ�δ�ڼ���
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


