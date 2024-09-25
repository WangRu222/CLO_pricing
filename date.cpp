#include "date.h"
#include <map>
// ****************************************************************
//--------------------------中国节假日数据--------------------------
static const valarray<string> holds_data =
{   "Jan  1 2020", "Jan 24 2020", "Jan 25 2020", "Jan 26 2020", "Jan 27 2020", "Jan 28 2020", "Jan 29 2020", "Jan 30 2020", "Apr  4 2020", "Apr  5 2020", "Apr  6 2020", "May  1 2020", "May  2 2020", "May  3 2020", "May  4 2020", "May  5 2020", "Jun 25 2020", "Jun 26 2020", "Jun 27 2020", "Oct  1 2020", "Oct  2 2020", "Oct  3 2020", "Oct  4 2020", "Oct  5 2020", "Oct  6 2020", "Oct  7 2020", "Oct  8 2020",
	"Jan  1 2021", "Jan  2 2021", "Jan  3 2021", "Feb 11 2021", "Feb 12 2021", "Feb 13 2021", "Feb 14 2021", "Feb 15 2021", "Feb 16 2021", "Feb 17 2021", "Apr  3 2021", "Apr  4 2021", "Apr  5 2021", "May  1 2021", "May  2 2021", "May  3 2021", "May  4 2021", "May  5 2021", "Jun 12 2021", "Jun 13 2021", "Jun 14 2021", "Sep 19 2021", "Sep 20 2021", "Sep 21 2021", "Oct  1 2021", "Oct  2 2021", "Oct  3 2021", "Oct  4 2021", "Oct  5 2021", "Oct  6 2021", "Oct  7 2021",
	"Jan  1 2022", "Jan  2 2022", "Jan  3 2022", "Jan 31 2022", "Feb  1 2022", "Feb  2 2022", "Feb  3 2022", "Feb  4 2022", "Feb  5 2022", "Feb  6 2022", "Apr  3 2022", "Apr  4 2022", "Apr  5 2022", "Apr 30 2022", "May  1 2022", "May  2 2022", "May  3 2022", "May  4 2022", "Jun  3 2022", "Jun  4 2022", "Jun  5 2022", "Sep 10 2022", "Sep 11 2022", "Sep 12 2022", "Oct  1 2022", "Oct  2 2022", "Oct  3 2021", "Oct  4 2022", "Oct  5 2022", "Oct  6 2022", "Oct  7 2022",
	"Jan  1 2023", "Jan 21 2023", "Jan 22 2023", "Jan 23 2023", "Jan 24 2023", "Jan 25 2023", "Jan 26 2023", "Jan 27 2023", "Apr  5 2023", "May  1 2023", "Jun 22 2023", "Sep 29 2023", "Oct  1 2023", "Oct  2 2023", "Oct  3 2023", "Oct  4 2023", "Oct  5 2023", "Oct  6 2023", "Oct  7 2023",
	"Jan  1 2024", "Feb  9 2024", "Feb 10 2024", "Feb 11 2024", "Feb 12 2024", "Feb 13 2024", "Feb 14 2024", "Feb 15 2024", "Apr  4 2024", "May  1 2024", "Jun 10 2024", "Sep 17 2024", "Oct  1 2024", "Oct  2 2024", "Oct  3 2024", "Oct  4 2024", "Oct  5 2024", "Oct  6 2024", "Oct  7 2024",
	"Jan  1 2025", "Jan 28 2025", "Jan 29 2025", "Jan 30 2025", "Jan 31 2025", "Feb  1 2025", "Feb  2 2025", "Feb  3 2025", "Apr  4 2025", "May  1 2025", "May 31 2025", "Oct  1 2025", "Oct  2 2025", "Oct  3 2025", "Oct  4 2025", "Oct  5 2025", "Oct  6 2025", "Oct  7 2025",
	"Jan  1 2026", "Feb 16 2026", "Feb 17 2026", "Feb 18 2026", "Feb 19 2026", "Feb 20 2026", "Feb 21 2026", "Feb 22 2026", "Apr  5 2026", "May  1 2026", "Jun 19 2026", "Sep 25 2026", "Oct  1 2026", "Oct  2 2026", "Oct  3 2026", "Oct  4 2026", "Oct  5 2026", "Oct  6 2026", "Oct  7 2026",
	"Jan  1 2027", "Feb  5 2027", "Feb  6 2027", "Feb  7 2027", "Feb  8 2027", "Feb  9 2027", "Feb 10 2027", "Feb 11 2027", "Apr  5 2027", "May  1 2027", "Jun  9 2027", "Sep 15 2027", "Oct  1 2027", "Oct  2 2027", "Oct  3 2027", "Oct  4 2027", "Oct  5 2027", "Oct  6 2027", "Oct  7 2027",
	"Jan  1 2028", "Jan 25 2028", "Jan 26 2028", "Jan 27 2028", "Jan 28 2028", "Jan 29 2028", "Jan 30 2028", "Jan 31 2028", "Apr  4 2028", "May  1 2028", "Jun 27 2028", "Oct  1 2028", "Oct  2 2028", "Oct  3 2028", "Oct  4 2028", "Oct  5 2028", "Oct  6 2028", "Oct  7 2028",
	"Jan  1 2029", "Feb 12 2029", "Feb 13 2029", "Feb 14 2029", "Feb 15 2029", "Feb 16 2029", "Feb 17 2029", "Feb 18 2029", "Apr  4 2029", "May  1 2029", "Jun 16 2029", "Sep 22 2029", "Oct  1 2029", "Oct  2 2029", "Oct  3 2029", "Oct  4 2029", "Oct  5 2029", "Oct  6 2029", "Oct  7 2029",
	"Jan  1 2030", "Feb  2 2030", "Feb  3 2030", "Feb  4 2023", "Feb  5 2030", "Feb  6 2030", "Feb  7 2030", "Feb  8 2030", "Apr  5 2030", "May  1 2030", "Jun  5 2030", "Sep 12 2030", "Oct  1 2030", "Oct  2 2030", "Oct  3 2030", "Oct  4 2030", "Oct  5 2030", "Oct  6 2030", "Oct  7 2030",
};
//--------------------------月份字符串对应相应月份数字--------------------------
static map<string, int> stringValues;
//--------------------------QDate定义时，用于初始化节假日（注意：所有的QDate维护相同的节假日，只在开始执行一次）--------------------------
static Array1I initialization()
{
	stringValues["Jan"] = 1;
	stringValues["Feb"] = 2;
	stringValues["Mar"] = 3;
	stringValues["Apr"] = 4;
	stringValues["May"] = 5;
	stringValues["Jun"] = 6;
	stringValues["Jul"] = 7;
	stringValues["Aug"] = 8;
	stringValues["Sep"] = 9;
	stringValues["Oct"] = 10;
	stringValues["Nov"] = 11;
	stringValues["Dec"] = 12;


	static int n = int(holds_data.size());
	Array1I hols_int(n);
	for (int i = 0; i < n; i++)
	{
		int year=0, month=0, day=0;
		const string temp = holds_data[i];
		//obtain day
		if (holds_data[1].substr(4, 1) == " ")
			day = atoi(temp.substr(5, 1).c_str());
		else day = atoi(temp.substr(4, 2).c_str());
		//obtain year
		year = atoi(temp.substr(7, 4).c_str());
		//obtain month
		month = stringValues[temp.substr(0, 3)];
		//printf("%d,%d,%d\n", year, month, day);
		hols_int[i] = YMD2Day(year, month, day);
	}
	return hols_int;
}



// ====================================QDateSpan - defines how dates are adjusted=================
QDateSpan::QDateSpan(unsigned long  lMonths, unsigned long lYears, unsigned long lDays, unsigned long lWeeks):m_lDays(lDays),m_lMonths(lMonths),m_lYears(lYears),m_lWeeks(lWeeks){}
QDateSpan::QDateSpan(const QDateSpan& qThatDateSpan){*this = qThatDateSpan;}
QDateSpan::QDateSpan():m_lDays(0),m_lMonths(0),m_lYears(0),m_lWeeks(0){}
const QDateSpan& QDateSpan::operator=(const QDateSpan& qThatDateSpan)
{
	m_lDays = qThatDateSpan.m_lDays;
	m_lMonths = qThatDateSpan.m_lMonths;
	m_lYears = qThatDateSpan.m_lYears;
	m_lWeeks = qThatDateSpan.m_lWeeks;
	return *this;
}
bool QDateSpan::operator==(const QDateSpan& qThatDateSpan) const
{
	return
		(
			m_lDays == qThatDateSpan.m_lDays &&
			m_lMonths == qThatDateSpan.m_lMonths &&
			m_lYears == qThatDateSpan.m_lYears &&
			m_lWeeks == qThatDateSpan.m_lWeeks
			);
}
QDateSpan& QDateSpan::operator+=(const QDateSpan& qThatDateSpan)
{
	m_lDays += qThatDateSpan.m_lDays;
	m_lMonths += qThatDateSpan.m_lMonths;
	m_lYears += qThatDateSpan.m_lYears;
	m_lWeeks += qThatDateSpan.m_lWeeks;

	return *this;
}
ostream& operator<<(ostream& os, const QDateSpan& tThat)
{
	os << "(" << tThat.Years() << ", " << tThat.Months() << ", " << tThat.Weeks() << ", " << tThat.Days() << ")" << endl;
	return os;
}
istream& operator>>(istream& is, QDateSpan& tThat)
{
	string sOpenBracket("("), sCloseBracket(")"), sComma(", ");
	is >> sOpenBracket >> tThat.Years() >> sComma >> tThat.Months() >> sComma >> tThat.Weeks() >> sComma >> tThat.Days() >> sCloseBracket;
	return is;
}



//==============================QSettlementCalc内部函数的定义=================================
QSettlementCalc::QSettlementCalc():m_nDaysToSettle(0),m_eSettlementCalcType(ESettlementCalcType::e_ActualDays),m_eAdjustConvention(EAdjustConvention::e_NoAdjustment){}
QSettlementCalc::QSettlementCalc(int nDaysToSettle,	ESettlementCalcType  eSettlementCalcType,EAdjustConvention    eAdjustConvention)
	: m_nDaysToSettle(nDaysToSettle),m_eSettlementCalcType(eSettlementCalcType),m_eAdjustConvention(eAdjustConvention){}
QSettlementCalc& QSettlementCalc::operator=(const QSettlementCalc& QSettlementCalc)
{
	m_nDaysToSettle = QSettlementCalc.m_nDaysToSettle;
	m_eSettlementCalcType = QSettlementCalc.m_eSettlementCalcType;
	m_eAdjustConvention = QSettlementCalc.m_eAdjustConvention;
	return *this;
}
bool QSettlementCalc::operator==(const QSettlementCalc& QSettlementCalc) const
{
	return (m_nDaysToSettle == QSettlementCalc.m_nDaysToSettle) &&
		(m_eSettlementCalcType == QSettlementCalc.m_eSettlementCalcType) &&
		(m_eAdjustConvention == QSettlementCalc.m_eAdjustConvention);
}
ostream& operator<<(ostream& os, const QSettlementCalc& cSettCalc)
{

	os << cSettCalc.DaysToSettle() << " ";
	os << int(cSettCalc.SettlementCalcType()) << " "<< int(cSettCalc.AdjustConvention());
	return os;
}
istream& operator>>(istream& is, QSettlementCalc& cSettCalc)
{
	int nSettlementCalcType;
	int nAdjustConvention;

	is >> cSettCalc.DaysToSettle();
	is >> nSettlementCalcType
		>> nAdjustConvention;

	cSettCalc.SettlementCalcType() = (ESettlementCalcType)nSettlementCalcType;
	cSettCalc.AdjustConvention() = (EAdjustConvention)nAdjustConvention;

	return is;
}
// ======================================================Frequency class===========================================
QFrequency::QFrequency(EFrequency eFrequency)
{
	switch (eFrequency)
	{
	case (EFrequency::e_Daily):
		m_lDays = 1;
		break;
	case (EFrequency::e_Weekly):
		m_lWeeks = 1;
		break;
	case (EFrequency::e_Monthly):
		m_lMonths = 1;
		break;
	case (EFrequency::e_BiMonthly):
		m_lMonths = 2;
		break;
	case (EFrequency::e_Quarterly):
		m_lMonths = 3;
		break;
	case (EFrequency::e_SemiAnnually):
		m_lMonths = 6;
		break;
	case (EFrequency::e_Annually):
		m_lYears = 1;
		break;
	case (EFrequency::e_Continuous):
		m_lDays = 1;
		break;
	default:
		throw("QFrequency - Invalid frequency : % d", (int)eFrequency);
		break;
	}
}
QFrequency::QFrequency(const char* szPeriod)
{
	unsigned long lPeriods(0);
	char szPeriodLength[256];

	// Allow for with or without dash
	if (sscanf_s(szPeriod, "%ld-%s", &lPeriods, szPeriodLength) != 2 &&
		sscanf_s(szPeriod, "%ld%s", &lPeriods, szPeriodLength) != 2)
	{
		throw("QFrequency: Invalid frequency string (\"%s\")", szPeriod);
	}

	string strPeriodLength(szPeriodLength);
	ToUpper(strPeriodLength);


	const char* szAllowedStrings[] = { "WEEK", "DAY", "MONTH", "YEAR" };
	size_t nMatchedIndex(0);
	size_t nMatches = ::MatchPS(szAllowedStrings, sizeof(szAllowedStrings) / sizeof(char*), strPeriodLength.c_str(), nMatchedIndex);
	if (nMatches == 1)
	{
		if (strcmp(szAllowedStrings[nMatchedIndex], "WEEK") == 0)
		{
			m_lWeeks = lPeriods;
		}
		else if (strcmp(szAllowedStrings[nMatchedIndex], "DAY") == 0)
		{
			m_lDays = lPeriods;
		}
		else if (strcmp(szAllowedStrings[nMatchedIndex], "MONTH") == 0)
		{
			m_lMonths = lPeriods;
		}
		else if (strcmp(szAllowedStrings[nMatchedIndex], "YEAR") == 0)
		{
			m_lYears = lPeriods;
		}
	}
	else if (nMatches == 2)
	{
		throw("QFrequency: Non unique match for frequency string: \"%s\"", szPeriod);
	}
	else
	{
		throw("QFrequency: Invalid frequency string (\"%s\")", szPeriod);
	}
}
QFrequency::operator string() const
{
	char szBuffer[256];
	if (!(m_lYears + m_lMonths + m_lWeeks))
	{   // Days
		sprintf_s(szBuffer, "%d-day", m_lDays);
	}
	else if (!(m_lYears + m_lMonths + m_lDays))
	{   // Weeks
		sprintf_s(szBuffer, "%d-week", m_lWeeks);
	}
	else if (!(m_lYears + m_lWeeks + m_lDays))
	{   // Months
		sprintf_s(szBuffer, "%d-month", m_lMonths);
	}
	else if (!(m_lMonths + m_lWeeks + m_lDays))
	{   // Years
		sprintf_s(szBuffer, "%d-year", m_lYears);
	}
	else
	{
		throw("QFrequency: Cannot convert QFrequency (%d,%d,%d,%d) to string",m_lYears, m_lMonths, m_lWeeks, m_lDays);
	}

	return string(szBuffer);
}
QFrequency::operator double() const
{
	if (m_lMonths)
	{
		return 12.0 / m_lMonths;
	}
	else if (m_lYears)
	{
		return 1.0 / m_lYears;
	}
	else if (m_lDays)
	{
		return 365.0 / m_lDays;
	}
	else if (m_lWeeks)
	{
		return 52.0 / m_lWeeks;
	}
	else
	{
		throw("Zero Frequency");
	}

	return 0.;
}
QFrequency::operator EFrequency() const
{
	if (m_lMonths==1)
	{
		return EFrequency::e_Monthly;
	}
	else if (m_lMonths == 2)
	{
		return EFrequency::e_BiMonthly;
	}
	else if (m_lMonths == 3)
	{
		return EFrequency::e_Quarterly;
	}
	else if (m_lMonths == 6)
	{
		return EFrequency::e_SemiAnnually;
	}
	else if (m_lYears == 1)
	{
		return EFrequency::e_Annually;
	}
	else if (m_lDays==1)
	{
		return EFrequency::e_Daily;
	}
	else if (m_lWeeks==1)
	{
		return EFrequency::e_Weekly;
	}
	else
	{
		throw("Zero Frequency");
	}

}
string QFrequency::shortString() const
{
	string ret;

	if ((Months() && !Years() && !Days() && !Weeks()) || ((1 == Years()) && !Months() && !Days() && !Weeks()))
	{
		double months = *this;
		if ((1 == months) || (2 == months) || (4 == months) || (12 == months))
			ret = stringFromMonths(12 / months);
	}

	if (!ret.length())
		return *this;

	return ret;
}
string QFrequency::stringFromMonths(int months)
{
	switch (months)
	{
		case 12:	return "A";
		case 6:		return "S";
		case 3:		return "Q";
		case 1:		return "M";
		case 0:		return "Z";
		default:	return "Unknown";
	}
}

//====================================QDate成员函数定义============================================
//=================================static成员变量和函数定义========================
size_t QDate::m_count = 0;
int* QDate::hols = nullptr;
size_t QDate::n_of_hols = 0;
void QDate::set_hols()
{
	hols = new int[holds_data.size()];
	Array1I temp = initialization();
	for (size_t i = 0; i < temp.size(); i++)hols[i] = temp[i];
	n_of_hols = temp.size();
	//printf("holds initialized!\n");
}
QDate::QDate(int _year, int _month, int _day)
{
	year = _year;
	month = _month;
	day = _day;
	ExcelDay = YMD2Day(year, month, day);

	if (hols == nullptr) set_hols();
	m_count++;

}
QDate::QDate(int _ExcelDay)
{
	int _year = 0, _month = 0, _day = 0;
	Day2YMD(_ExcelDay, &_year, &_month, &_day);
	year = _year;
	month = _month;
	day = _day;
	ExcelDay = _ExcelDay;

	if (hols == nullptr)set_hols();
	m_count++;
}
QDate::QDate(const std::string datestr)
{
	if (datestr.find("-") != std::string::npos || datestr.find("/") != std::string::npos)
	{
		std::string year0 = "";
		std::string month0 = "";
		std::string day0 = "";

		if (datestr.size() == 10)
		{
			//说明日期的年月日用-、|分割,如2021-10-09 或者2021/10/09
			year0 = datestr.substr(0, 4);
			month0 = datestr.substr(5, 2);
			day0 = datestr.substr(8, 2);
		}
		else if ((datestr.size() == 8 || datestr.size() == 9))
		{
			if (datestr.find("/") != std::string::npos)
			{
				//若为2029/4/30， 以下四个值分别为4，6，1，2
				//若为2023/1/1，  以下四个值分别为4，6，1，1
				int first = datestr.find_first_of("/");
				int second = datestr.find_last_of("/");
				int first_size = second - first - 1;
				int second_size = datestr.size() - second - 1;
				year0 = datestr.substr(0, 4);
				month0 = datestr.substr(first, first_size);
				day0 = datestr.substr(second,second_size);
			}
			else if (datestr.find("-") != std::string::npos)
			{
				//若为2029-4-30， 以下四个值分别为4，6，1，2
				//若为2023-1-1，  以下四个值分别为4，6，1，1
				int first = datestr.find_first_of("-");
				int second = datestr.find_last_of("-");
				int first_size = second - first - 1;
				int second_size = datestr.size() - second - 1;
				year0 = datestr.substr(0, 4);
				month0 = datestr.substr(first, first_size);
				day0 = datestr.substr(second, second_size);
			}
		}


		//c_str()函数返回一个指向正规C字符串的指针常量, 内容与本string串相同.这是为了与c语言兼容，
		//在c语言中没有string类型，故必须通过string类对象的成员函数c_str()把string 对象转换成c中的字符串样式。

		//atoi( ) 函数会扫描参数字符串，跳过前面的空白字符（例如空格，tab缩进等，可以通过isspace( )函数来检测），
		//直到遇上数字或正负符号才开始做转换，而再遇到非数字或字符串结束时('\0')才结束转换，并将结果返回。
		//如果 nptr不能转换成 int 或者 nptr为空字符串，那么将返回 0。

		year = atoi(year0.c_str());
		month = atoi(month0.c_str());
		day = atoi(day0.c_str());
		ExcelDay = YMD2Day(year, month, day);

		if (hols == nullptr) set_hols();
		m_count++;


	}
	else if (datestr.length() == 8)
	{
		//如 20211009
		std::string year0 = datestr.substr(0, 4);
		std::string month0 = datestr.substr(4, 2);
		std::string day0 = datestr.substr(6, 2);
		year = atoi(year0.c_str());
		month = atoi(month0.c_str());
		day = atoi(day0.c_str());
		ExcelDay = YMD2Day(year, month, day);

		if (hols == nullptr) set_hols();
		m_count++;
	}
	else throw"Error date string type!!!";

}
QDate::QDate(const QDate& obj)
{
	ExcelDay = obj.ExcelDay;
	year = obj.year;
	month = obj.month;
	day = obj.day;

	if (hols == nullptr) set_hols();
	m_count++;
}
QDate::~QDate(void)
{
	m_count--;
	//printf("析构函数正在执行，当前对象数：%d\n", m_count);
	if (m_count == 0) {
		delete[] hols; hols = nullptr;
		//printf("hols has been freed!!\n");
	}
}

//QDate与天数相加
QDate QDate::operator+(const int days)
{
	//QDate d1 = d0+ 5;//注意：这里不能+5之后改变了d0自身的值
	QDate temp_date = *this;//copy构造函数，构造了一个新对象
	temp_date.ExcelDay = ExcelDay + days;
	int _year = 0, _month = 0, _day = 0;
	Day2YMD(temp_date.ExcelDay, &_year, &_month, &_day);
	year = _year;
	month = _month;
	day = _day;

	return temp_date;
}
QDate QDate::operator-(const int days)
{
	//QDate d1 = d0+ 5;//注意：这里不能+5之后改变了d0自身的值
	QDate temp_date = *this;//copy构造函数，构造了一个新对象
	temp_date.ExcelDay = ExcelDay - days;
	int _year = 0, _month = 0, _day = 0;
	Day2YMD(temp_date.ExcelDay, &_year, &_month, &_day);
	year = _year;
	month = _month;
	day = _day;

	return temp_date;
}
//两个QDate之间互相比较
QDate& QDate::operator=(const QDate& qd0)
{
	ExcelDay = qd0.ExcelDay;
	year = qd0.year;
	month = qd0.month;
	day = qd0.day;
	return *this;

}
QDate& QDate::operator=(int i0)
{
	if (i0 == 0) i0 = 1;
	int _year = 0, _month = 0, _day = 0;
	Day2YMD(i0, &_year, &_month, &_day);
	year = _year;
	month = _month;
	day = _day;
	ExcelDay = i0;
	return *this;
}
QDate& QDate::operator++() 
{ 
	ExcelDay++; 
	Day2YMD(ExcelDay, &year, &month, &day); 
	return *this; 
}
QDate& QDate::operator--() 
{ 
	ExcelDay--; 
	Day2YMD(ExcelDay, &year, &month, &day); 
	return *this; 
}
bool QDate::operator < (const QDate& qd0) const
{
	if (ExcelDay < qd0.getExcelDay()) return true;
	else return false;
}
bool QDate::operator > (const QDate& qd0) const
{
	if (ExcelDay > qd0.getExcelDay()) return true;
	else return false;
}
bool QDate::operator <= (const QDate& qd0) const
{
	if (ExcelDay <= qd0.getExcelDay()) return true;
	else return false;
}
bool QDate::operator >= (const QDate& qd0) const
{
	if (ExcelDay >= qd0.getExcelDay()) return true;
	else return false;
}
bool QDate::operator == (const QDate& qd0) const
{
	if (ExcelDay == qd0.getExcelDay()) return true;
	else return false;
}
bool QDate::operator != (const QDate& qd0) const
{
	if (ExcelDay != qd0.getExcelDay()) return true;
	else return false;
}
QDate& QDate::operator+=(const QDateSpan& qThat)
{
	// Add years / months
	unsigned long lMonths = (unsigned long)(qThat.Years() * 12) + qThat.Months();
	AddMonths(lMonths);//在当前的日期上加上特定的月数 
	// Add any remaining days
	unsigned long lDays = qThat.Weeks() * 7 + qThat.Days();
	*this += lDays;//在当前日期上加上特定的天数
	return *this;
}
QDate& QDate::operator-=(const QDateSpan& qThat)
{
	// Add years / months
	unsigned long lMonths = (unsigned long)(qThat.Years() * 12) + qThat.Months();
	MinusMonths(lMonths);//在当前的日期上加上特定的月数 
	// Add any remaining days
	unsigned long lDays = qThat.Weeks() * 7 + qThat.Days();
	*this -= lDays;//在当前日期上加上特定的天数
	return *this;
}

bool QDate::isleap()
{
	if ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0)) return true;
	else return false;
}

bool QDate::isleap() const
{
	if ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0)) return true;
	else return false;
}
int QDate::EndOfMonth() const
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
	else
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year) % 400 == 0)//闰年
		{
			return 29;
		}
		else return 28;
	}
}
int QDate::EndOfMonth()
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
	else
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year) % 400 == 0)//闰年
		{
			return 29;
		}
		else return 28;
	}
}

//将QDate类型转化为string类型
//返回得日期得字符串形如"20230631"，共8位；
string QDate::dateToString()//将date转为string类型, 示例:20230631
{
	string str = to_string(year);
	if (month < 10) str = str + "0" + to_string(month);
	else str = str + to_string(month);
	if (day < 10)str = str + "0" + to_string(day);
	else str = str + to_string(day);
	return str;
}
string QDate::dateToString() const //将date转为string类型
{
	string str = to_string(year);
	if (month < 10) str = str + "0" + to_string(month);
	else str = str + to_string(month);
	if (day < 10)str = str + "0" + to_string(day);
	else str = str + to_string(day);
	return str;
}


string QDate::dateToString(int String_type)
{
	if (String_type == 0) 
	{
		//将date转为string类型, 示例:20230631
		string str = to_string(year);
		if (month < 10) str = str + "0" + to_string(month);
		else str = str + to_string(month);
		if (day < 10)str = str + "0" + to_string(day);
		else str = str + to_string(day);
		return str;
	}
	else if (String_type == 1)
	{
		//将date转为string类型, 示例:2023/06/31
		string str = to_string(year);
		if (month < 10) str = str + "/0" + to_string(month);
		else str = str +"/" + to_string(month);
		if (day < 10)str = str + "/0" + to_string(day);
		else str = str + "/" + to_string(day);
		return str;
	}
	else if (String_type == 2)
	{
		//将date转为string类型, 示例:2023-06-31
		string str = to_string(year);
		if (month < 10) str = str + "-0" + to_string(month);
		else str = str + "-" + to_string(month);
		if (day < 10)str = str + "-0" + to_string(day);
		else str = str + "-" + to_string(day);
		return str;
	}
}
string QDate::dateToString(int String_type) const //将date转为string类型
{
	if (String_type == 0)
	{
		//将date转为string类型, 示例:20230631
		string str = to_string(year);
		if (month < 10) str = str + "0" + to_string(month);
		else str = str + to_string(month);
		if (day < 10)str = str + "0" + to_string(day);
		else str = str + to_string(day);
		return str;
	}
	else if (String_type == 1)
	{
		//将date转为string类型, 示例:2023/06/31
		string str = to_string(year);
		if (month < 10) str = str + "/0" + to_string(month);
		else str = str + "/" + to_string(month);
		if (day < 10)str = str + "/0" + to_string(day);
		else str = str + "/" + to_string(day);
		return str;
	}
	else if (String_type == 2)
	{
		//将date转为string类型, 示例:2023-06-31
		string str = to_string(year);
		if (month < 10) str = str + "-0" + to_string(month);
		else str = str + "-" + to_string(month);
		if (day < 10)str = str + "-0" + to_string(day);
		else str = str + "-" + to_string(day);
		return str;
	}
}

//=================加上固定周期的时间，未考虑是否为工作日==============
void QDate::AddDays(int days)
{
	ExcelDay = ExcelDay + days;
	Day2YMD(ExcelDay, &year, &month, &day);
}
void QDate::AddWeeks(int weeks)
{
	ExcelDay = ExcelDay + 7 * weeks;
	Day2YMD(ExcelDay, &year, &month, &day);
}
void QDate::AddMonths(int months)
{
	ExcelDay = addMonth(ExcelDay, months);
	Day2YMD(ExcelDay, &year, &month, &day);
}
void QDate::AddYears(int years)
{
	ExcelDay = addYear(ExcelDay, years);
	Day2YMD(ExcelDay, &year, &month, &day);
}
// Function: QDate AddYears(double dYears, bool bTruncateDay) OVERLOADED
// Description: Adds a DOUBLE number of years to the date. 
// Input:dYears: The number of years to add.
// Output return: The number of days actually added.
double QDate::AddYears(double dYears, EAccrualBasis eAccrualBasis, bool bTruncateDay)
{
	int ed  = ExcelDay;

	switch (eAccrualBasis)
	{
		case EAccrualBasis::e_Act365:
			(*this) += dYears * 365.0;
			break;

		case EAccrualBasis::e_Act360:
			(*this) += dYears * 360.0;
			break;

		case EAccrualBasis::e_30360:
		case EAccrualBasis::e_30E360:
		{
			int nYearsToAdd = (int)floor(dYears);
			double dMonths = (dYears - (double)nYearsToAdd) * 12.0;

			int nMonthsToAdd = (int)floor(dMonths);
			double dDaysToAdd = (dMonths - (double)nMonthsToAdd) * 30.0;

			int nCurrentMonth = month, nCurrentYear=year, dCurrentDay=day;
			if (dCurrentDay >= 31.0) dCurrentDay--;

			int dNewDay = dCurrentDay + dDaysToAdd;
			int nNewMonth = nCurrentMonth + nMonthsToAdd;
			int nNewYear = nCurrentYear + nYearsToAdd;

			if (dNewDay >= 31.0)
			{
				dNewDay -= 30.0;
				nNewMonth++;
			}
			if (nNewMonth > 12)
			{
				nNewMonth -= 12;
				nNewYear++;
			}

			unsigned int nLastDayOfNewMonth = daysInMonthYear(nNewMonth, nNewYear);
			if ((unsigned)dNewDay > nLastDayOfNewMonth)
			{
				dNewDay = 1.0 + fmod(dNewDay, 1.0);
				nNewMonth++;
			}
			if (nNewMonth > 12)
			{
				nNewMonth -= 12;
				nNewYear++;
			}

			(*this) = QDate(nNewYear,nNewMonth, dNewDay);
		}
		break;

		case EAccrualBasis::e_ActAct:
		case EAccrualBasis::e_Act29:
		case EAccrualBasis::e_Coupon:
		{
			double dSign = (dYears >= 0.0 ? 1.0 : -1.0);
			dYears *= dSign;

			int nYear = (dSign == 1.0 ? year + 1 : year);
			QDate tFirstInYear(nYear,1, 1);
			double dTimeInYear = dSign * (tFirstInYear.getExcelDay() - this->getExcelDay()) / daysInYear(year);

			// Add days in the first year
			(*this) += dSign * MIN(dYears, dTimeInYear) * daysInYear(year);
			double dLeftToAdd = MAX(dYears - dTimeInYear, 0.0);

			// Add any whole years
			if (dLeftToAdd >= 1.0)
			{
				dLeftToAdd -= (int)dLeftToAdd;
			}

			// Add days in the last year
			nYear = (dSign == 1.0 ? year: year - 1);
			(*this) += dSign * dLeftToAdd * daysInYear(nYear);
		}
		break;

		default:
			throw("AddYears - Invalid accrual basis: %d", (int)eAccrualBasis);
	}


	return ExcelDay - ed;
}
double QDate::AddYears(double dYears, bool bTruncateDay)
{
	double ed = ExcelDay;

	double dWholeYears;
	double dFraction = modf(dYears, &dWholeYears);//dWholeYears为除以1的整数部分；dFraction为小数部分

	// Add whole number of years
	AddYears((int)dWholeYears);

	// Add fractional number of years at ActAct
	if (dFraction) AddYears(dFraction, EAccrualBasis::e_ActAct, bTruncateDay);

	return (ExcelDay - ed);
}
void QDate::MinusMonths(int months)
{

	int	d1 = day;
	int	m1 = month - 1 - months;			// Months (jan=0);
	int dy = 0;
	while (m1 < 0)
	{
		m1 = m1 + 12;
		dy++;//需要减去的年数
	}
	int	m2 = (m1 % 12 + 12) % 12 + 1;		// Months+m (jan=1)
	int	y1 = year - dy;
	if (d1 > monthDay[m2]) d1 = monthDay[m2];	// Don't exceed days per month.
	if (y1 % 4 != 0 || y1 % 100 == 0 && y1 % 400 != 0) {
		if (m2 == 2 && d1 > 28) d1 = 28;			// Don't feb 28 unless leap year.
	}
	ExcelDay = YMD2Day(y1, m2, d1);
	Day2YMD(ExcelDay, &year, &month, &day);

}
void QDate::MinusYears(int years)
{

	int	d1 = day;
	int	m1 = month;			// Months (jan=0);
	int	y1 = year - years;
	if (y1 % 4 != 0 || y1 % 100 == 0 && y1 % 400 != 0) {
		if (m1 == 2 && d1 > 28) d1 = 28;			// Don't feb 28 unless leap year.
	}
	ExcelDay = YMD2Day(y1, m1, d1);
	Day2YMD(ExcelDay, &year, &month, &day);
}
QDate& QDate::operator+=(double dDays) //在自身的基础上加上特定的天数，改变自身
{
	ExcelDay = ExcelDay + dDays;
	Day2YMD(ExcelDay, &year, &month, &day);
	return *this;
}
QDate& QDate::operator-=(double dDays) //在自身的基础上加上特定的天数，改变自身
{
	ExcelDay = ExcelDay - dDays;
	Day2YMD(ExcelDay, &year, &month, &day);
	return *this;
}
int QDate::AdjustToStartOfMonth()
{
	int d1 = day;
	int m1 = month;
	int y1 = year;
	ExcelDay = YMD2Day(y1, m1, 1);//获取当月第一天的ExcelDay
	Day2YMD(ExcelDay, &year, &month, &day);//将ExcelDay的数据覆盖year,month,day
	return (1 - d1);//本身为1，返回0； 本身为2，返回-1，......,也就是往前调整的天数，为负数
}
int QDate::AdjustToEndOfMonth()
{
	int d1 = day;
	int m1 = month;
	int y1 = year;

	int endDay = EndOfMonth();
	ExcelDay = YMD2Day(y1, m1, endDay);//获取当月最后一天的ExcelDay
	Day2YMD(ExcelDay, &year, &month, &day);//将ExcelDay的数据覆盖year,month,day

	return (endDay - d1);
}
int QDate::AdjustToBusiness(EAdjustConvention eAdjustConvention)
{
	int nDaysAdj;

	switch (eAdjustConvention)
	{
	case EAdjustConvention::e_ModifiedFollowing:
		nDaysAdj = MFBD_int() - ExcelDay;
		break;
	case EAdjustConvention::e_Following:
		nDaysAdj = FBD_int() - ExcelDay;
		break;
	case EAdjustConvention::e_Preceding:
		nDaysAdj = PBD_int() - ExcelDay;
		break;
	case EAdjustConvention::e_NoAdjustment:
		nDaysAdj = 0;// Do nothing
		break;
	case EAdjustConvention::e_ModifiedPreceding:
		nDaysAdj = MPBD_int() - ExcelDay;
		break;
	default:
		throw("AdjustToBusiness: Invalid adjust convention (%d)", (int)eAdjustConvention);
		break;
	}

	ExcelDay = ExcelDay + nDaysAdj;
	Day2YMD(ExcelDay, &year, &month, &day);

	return nDaysAdj;
}
int QDate::AddBusinessDays(int nBusinessDays)
{
	int nAdjustedDays(0);

	if (nBusinessDays > 0)
	{
		for (int ni = 0; ni < nBusinessDays; ni++)
		{
			ExcelDay = ExcelDay + 1;
			Day2YMD(ExcelDay, &year, &month, &day);
			// if this is not a Biz day adjust it to a Biz Day. Allways use following.
			nAdjustedDays += AdjustToBusiness(EAdjustConvention::e_Following);//AdjustToBusiness这个函数本身会改变自身的值
		}
	}
	else if (nBusinessDays < 0) // subtracting
	{
		for (int ni = 0; ni > nBusinessDays; ni--)
		{
			ExcelDay = ExcelDay - 1;
			Day2YMD(ExcelDay, &year, &month, &day);
			// if this is not a Biz day adjust it to a Biz Day.
			nAdjustedDays += AdjustToBusiness(EAdjustConvention::e_Preceding);
		}
	}

	return nBusinessDays + nAdjustedDays;
}
QDate QDate::SettlementDate(const QSettlementCalc& qSettlementCalc) const
{
	QDate tSettlement(*this);

	switch (qSettlementCalc.SettlementCalcType())
	{
	case ESettlementCalcType::e_ActualDays:
		tSettlement += qSettlementCalc.DaysToSettle();
		tSettlement.AdjustToBusiness(qSettlementCalc.AdjustConvention());
		break;

	case ESettlementCalcType::e_BusinessDays:
		tSettlement.AddBusinessDays(qSettlementCalc.DaysToSettle());
		break;

	case ESettlementCalcType::e_NextEndOfMonth:
		tSettlement.AdjustToEndOfMonth();
		tSettlement.AdjustToBusiness(qSettlementCalc.AdjustConvention());
		if (5 >= BusinessDaysBetween(*this, tSettlement))
		{
			tSettlement.AddMonths(1);
			tSettlement.AdjustToEndOfMonth();
			tSettlement.AdjustToBusiness(qSettlementCalc.AdjustConvention());
		}
		break;
	}

	return tSettlement;
}

//================可选择加上固定周期时间后为工作日=====================
QDate QDate::AddPeriod(int step, char unit, bool biz_day_adjust)const
{
	QDate result_date;
	QDate temp_date = *this;//copy构造函数，构造了一个新对象
	switch (unit) {
	case 'd':
	case 'D':
		//date_duration period(step);
		temp_date.AddDays(step);
		if (biz_day_adjust)
			result_date = temp_date.FBD_date();
		else result_date = temp_date;
		break;
	case 'w':
	case 'W':
		//date_duration period(step*7);
		temp_date.AddWeeks(step);
		if (biz_day_adjust)
			result_date = temp_date.FBD_date();
		else result_date = temp_date;
		break;
	case 'm':
	case 'M':
		//add_month period(step);
		temp_date.AddMonths(step);
		if (biz_day_adjust)
			result_date = temp_date.MFBD_date();
		else result_date = temp_date;
		break;
	case 'q':
	case 'Q':
		//add_month period(step);
		temp_date.AddMonths(3*step);
		if (biz_day_adjust)
			result_date = temp_date.MFBD_date();
		else result_date = temp_date;
		break;
	case 'y':
	case 'Y':
		temp_date.AddYears(step);
		// std::cout << "temp_date" << temp_date << std::endl;
		if (biz_day_adjust)
			result_date = temp_date.MFBD_date();
		else result_date = temp_date;
		break;
	default:
		result_date = *this;
		printf("%c-----------------\n", unit);
		throw "warning in AddPeriod: unrecognized period unit";
	}
	return result_date;
}
QDate QDate::MinusPeriod(int step, char unit, bool biz_day_adjust)const
{
	QDate result_date;
	QDate temp_date = *this;//copy构造函数，构造了一个新对象
	switch (unit) {
	case 'd':
	case 'D':
		//date_duration period(step);
		temp_date = temp_date - step;
		if (biz_day_adjust)
			result_date = temp_date.PBD_date();
		else result_date = temp_date;
		break;
	case 'w':
	case 'W':
		//date_duration period(step*7);
		temp_date = temp_date - 7*step;
		if (biz_day_adjust)
			result_date = temp_date.PBD_date();
		else result_date = temp_date;
		break;
	case 'm':
	case 'M':
		//add_month period(step);
		temp_date.MinusMonths(step);
		if (biz_day_adjust)
			result_date = temp_date.PBD_date();
		else result_date = temp_date;
		break;
	case 'y':
	case 'Y':
		temp_date.MinusYears(step);
		// std::cout << "temp_date" << temp_date << std::endl;
		if (biz_day_adjust)
			result_date = temp_date.PBD_date();
		else result_date = temp_date;
		break;
	default:
		result_date = *this;
		throw "warning in AddPeriod: unrecognized period unit";
	}
	return result_date;
}
int QDate::EndAddMonths(int months)
{
	return monthEnd(ExcelDay, months);
}
bool QDate::isHoliday() const
{
	int flag = 0;
	//n：holiday数组的长度
	//hols： 节假日数组
	flag = isHol(ExcelDay, n_of_hols, hols);//周末或在hols中，返回1； 否则返回0；hols为空，则假设任何日期都不在hols中
	if (flag == 1)return true;
	else return false;
}

bool QDate::isBusinessDay() const
{
	return !isHoliday();
}
bool QDate::isWeekend() const
{
	int week = (ExcelDay - 2) % 7 + 1;
	if (week == 6 || week == 7) return true;
	else return false;
}
bool QDate::IsBetween(QDate date1, QDate date2) const
{
	if (ExcelDay <= date2.getExcelDay() && ExcelDay >= date1.getExcelDay()) return true;
	if (ExcelDay <= date1.getExcelDay() && ExcelDay >= date2.getExcelDay()) return true;
	return false;
}
bool QDate::IsMonthEnd() const
{
	if (month != 2)
	{
		if (day == monthCum[month]) return true;
		else return false;
	}
	else
	{
		if (isleap() == true && day == 29) return true;
		else if (isleap() == false && day == 28) return true;
		else return false;
	}
	
	
}

int QDate::AddWorkdays(int days)
{
	return workDay(ExcelDay, days, n_of_hols, hols);
}
//================返回下一个，上一个工作日；自身为工作日，返回自身======
int QDate::MFBD_int()
{
	return MFBD(ExcelDay, n_of_hols, hols);

}
QDate QDate::MFBD_date()
{
	int d0 = MFBD(ExcelDay, n_of_hols, hols);
	QDate qd0 = QDate(d0);
	return qd0;
}
int QDate::MPBD_int()
{
	return MPBD(ExcelDay, n_of_hols, hols);

}
QDate QDate::MPBD_date()
{
	int d0 = MPBD(ExcelDay, n_of_hols, hols);
	QDate qd0 = QDate(d0);
	return qd0;
}
int QDate::FBD_int()
{
	int	dt;
	for (dt = ExcelDay; isHol(dt, n_of_hols, hols); dt++);		// Move to next working day.
	//不管下个工作日是否在下个月，只管取下个工作日
	return dt;
}
QDate QDate::FBD_date()
{
	int	dt;
	for (dt = ExcelDay; isHol(dt, n_of_hols, hols); dt++);		// Move to next working day.
	//不管下个工作日是否在下个月，只管取下个工作日
	QDate qd0 = QDate(dt);
	return qd0;

}
int QDate::PBD_int()
{
	int	dt;
	for (dt = ExcelDay; isHol(dt, n_of_hols, hols); dt--);		// Move to next working day.
	//不管下个工作日是否在下个月，只管取下个工作日
	return dt;
}
QDate QDate::PBD_date()
{
	int	dt;
	for (dt = ExcelDay; isHol(dt, n_of_hols, hols); dt--);		// Move to next working day.
	//不管下个工作日是否在下个月，只管取下个工作日
	QDate qd0 = QDate(dt);
	return qd0;

}
QDate QDate::NthDayOfWeekInMonth(unsigned Nth, unsigned weekday) const
{
	QDate firstday(year, month, 1);
	int firstdayInMonth = firstday.getExcelDay();
	int firstWeekday = firstday.Week();

	if (firstWeekday <= weekday)
	{
		firstdayInMonth = firstdayInMonth + (weekday - firstWeekday);//这个第1st的weekday对应日期的excelday
	}
	else
	{
		firstdayInMonth = firstdayInMonth + (weekday - firstWeekday)+7;//这个第1st的weekday对应日期的excelday
	}

	firstdayInMonth = firstdayInMonth + 7*(Nth-1);

	QDate res(firstdayInMonth);
	if (res.Month() == month)return res;
	else throw("The corresponding date is not in this month, please check!!!");
}
QDate QDate::GetIMMDate(int nIMMDateNum, const QFrequency& qFrequency, unsigned nDayOfWeek, bool bNext) const
{
	QDate tCalcDate(*this);
	int nSign;

	if (bNext)
	{
		nSign = 1; //Adding or Subtracting Months
	}
	else
	{
		nSign = -1;
	}

	if (qFrequency == EFrequency::e_Monthly)//这里==调用QFrequency中的隐式类型转化，将QFrequency转化为EFrequency
	{
		//Check if we count this Month or Not.
		if (tCalcDate >= tCalcDate.NthDayOfWeekInMonth(3,nDayOfWeek))
		{
			// we are after this months IMM
			if (nSign == 1)
			{
				tCalcDate.AddMonths(nSign * nIMMDateNum);
			}
			else
			{
				tCalcDate.MinusMonths(-nSign * (nIMMDateNum - 1));
			}
		}
		else
		{
			// we are before this months IMM
			if (nSign == 1)
			{
				tCalcDate.AddMonths(nSign * (nIMMDateNum - 1));
			}
			else
			{
				tCalcDate.MinusMonths(-nSign * nIMMDateNum);
			}
		}
	}
	else // Default if( QFrequency == e_Quarterly)
	{
		if (tCalcDate.Month() % 3 == 0) // We are in An Imm Month
		{
			//Check if we count this Month or Not.
			if (tCalcDate >= tCalcDate.NthDayOfWeekInMonth(3,nDayOfWeek))
			{
				// we are on or after this months IMM
				if (nSign == 1)
				{
					tCalcDate.AddMonths(nSign * 3 * nIMMDateNum);
				}
				else
				{
					tCalcDate.MinusMonths(-nSign * 3 * (nIMMDateNum - 1));
				}
			}
			else
			{
				// we are before this months IMM
				if (nSign == 1)
				{
					tCalcDate.AddMonths(nSign * 3 * (nIMMDateNum - 1));
				}
				else
				{
					tCalcDate.MinusMonths(-nSign * 3 * nIMMDateNum);
				}
			}
		}
		else // Not in an IMM Month, easiest
		{
			while (tCalcDate.Month() % 3) // Iterate until we find a month divisable by 3
			{
				tCalcDate.AddMonths(nSign); // Next / Prev Quarterly IMM Month
			}
			// Moved to One  IMM already

			tCalcDate.AddMonths(nSign * 3 * (nIMMDateNum - 1)); // Adjust the Number of Quarters
		}
	}

	// Adjust to an IMM Date within the current Month
	// 以上程序部分只是调整到特定的月份，下面的一句是将当月调整到相应的正确的日期。即为第三个星期三
	tCalcDate = tCalcDate.NthDayOfWeekInMonth(3,nDayOfWeek); // Third Wedensday
	return tCalcDate;
}
int QDate::AdjustToImm(const QFrequency& qFrequency, bool bNext, unsigned nDayOfWeek, int nIMMDateNum )
{
	int dOldDate = ExcelDay;
	*this = GetIMMDate(nIMMDateNum, qFrequency, nDayOfWeek, bNext);//改变自身
	return ExcelDay - dOldDate;
}
bool QDate::IsBetween(const QDate& tDateIn, const QDate& tDate1, const QDate& tDate2)
{
	if (tDateIn >= tDate1 && tDateIn <= tDate2) return true;
	else if (tDateIn >= tDate2 && tDateIn <= tDate1) return true;
	return false;


}
// returns true if 29 Feb falls between these two dates
bool QDate::SpansLeapDay(const QDate& tDate1, const QDate& tDate2)
{
	if (tDate1 > tDate2) throw("Start date (%s) comes after end date (%s)", tDate1.dateToString(), tDate2.dateToString());

	for (int thisYear = tDate1.Year(); thisYear <= tDate2.Year(); ++thisYear)
	{
		if (leapYear(thisYear))
		{
			QDate tLeapDay(2, 29, thisYear);
			if (IsBetween(tLeapDay, tDate1, tDate2)) return true;
		}
	}

	return false;
}
double  QDate::YearFraction(const QDate& tStartDate, const QDate& tEndDate, EAccrualBasis eAccrualBasis)
{
	if (tStartDate > tEndDate)
	{
		throw("YearFraction:Start date (%s) comes after end date (%s)",tStartDate.dateToString(), tEndDate.dateToString());
	}

	if (tStartDate == tEndDate)
	{
		return 0.0;
	}

	double dYearFraction(0);
	int nStartYear(tStartDate.Year());
	int nEndYear(tEndDate.Year());

	//情形一
	if (eAccrualBasis == EAccrualBasis::e_ActAct && SpansLeapYear(tStartDate, tEndDate))
	{
		if (nStartYear == nEndYear)// Same year - a leap year
		{   
			dYearFraction += (double)(tEndDate - tStartDate) / daysInYear(nStartYear);
		}
		else
		{   // Different years
			// Calculate the year fraction from the start date to the end of its year
			QDate tFirstDayOfYear(1, 1, nStartYear + 1);
			dYearFraction += (double)(tFirstDayOfYear.getExcelDay() - tStartDate.getExcelDay()) / daysInYear(nStartYear);

			// Add contributions from intermediate years
			dYearFraction += (nEndYear - (nStartYear + 1));

			// Calculate the year fraction from the start of the end year to the last date
			QDate tLastDayOfYear(1, 1, nEndYear);
			dYearFraction += (tEndDate.getExcelDay() - tLastDayOfYear.getExcelDay()) / daysInYear(nEndYear);
		}
	}
	//情形二
	else if (eAccrualBasis == EAccrualBasis::e_Act29)
	{
		//分子：act
		//分母：日期间包含2-29，则分母用366；否则用365
		if (SpansLeapDay(tStartDate, tEndDate))
		{
			dYearFraction = (tEndDate.getExcelDay() - tStartDate.getExcelDay()) / 366.;
		}
		else
		{
			dYearFraction = (tEndDate.getExcelDay() - tStartDate.getExcelDay()) / 365.;
		}
	}
	//情形三
	else if (eAccrualBasis == EAccrualBasis::e_Coupon)
	{
		double dNumerator = BasisDaysBetween(tStartDate, tEndDate, EAccrualBasis::e_30360);
		double dDenominator = BasisDaysInYear(EAccrualBasis::e_30360, nEndYear);
		dYearFraction = dNumerator / dDenominator;

		if (dYearFraction < 1.03 && dYearFraction > 0.97)
			dYearFraction = 1.0;
		else if (dYearFraction < 0.53 && dYearFraction > 0.47)
			dYearFraction = 0.5;
		else if (dYearFraction < 0.28 && dYearFraction > 0.22)
			dYearFraction = 0.25;
	}
	//情形四
	else
	{	//情形四处理以下多种情形：
		//e_ActAct：且不包括闰年。如果包括闰年，需要逐年计算并相加，即情形一
		//e_Act360：
		//e_Act365:
		//e_30360：
		//e_30E360:
		double dNumerator = BasisDaysBetween(tStartDate, tEndDate, eAccrualBasis);//根据eAccrualBasis的不同，要不要对31号进行特别处理
		double dDenominator = BasisDaysInYear(eAccrualBasis, nEndYear);//根据eAccrualBasis的不同，确定时365还是360
		dYearFraction = dNumerator / dDenominator;
	}

	return dYearFraction;

}
double  QDate::YearFraction(const QDate& tStartDate, const QDate& tEndDate, EAccrualBasis eAccrualBasis, EFrequency eFreq)
{
	if (tStartDate > tEndDate)
	{
		throw("YearFraction:Start date (%s) comes after end date (%s)",tStartDate.dateToString(), tEndDate.dateToString());
	}

	double dYearFraction(0);

	if (eAccrualBasis == EAccrualBasis::e_Coupon)
	{

		switch (eFreq)
		{
		case EFrequency::e_Annually:
			return (1.);
			break;
		case EFrequency::e_SemiAnnually:
			return (0.5);
			break;
		case EFrequency::e_Quarterly:
			return (0.25);
			break;
		default:
			throw("QDate::YearFraction coupon basis is not supported for this frequency");
			break;
		}
	}
	else
	{
		dYearFraction = YearFraction(tStartDate, tEndDate, eAccrualBasis);
	}

	return dYearFraction;
}
bool QDate::SpansLeapYear(const QDate& tStartDate, const QDate& tEndDate)
{
	if(tStartDate > tEndDate)throw"Error:startDate > endDate!!!";

	int nStartYear = tStartDate.Year();
	int nEndYear = tEndDate.Year();

	for (int nYear = nStartYear; nYear <= nEndYear; nYear++)
	{
		if ((nYear) % 4 == 0 && ((nYear) % 100 != 0 || (nYear) % 400 == 0)) return true;
	}
	return false;
}
bool QDate::leapYear(unsigned year)
{
	if ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0)) return true;
	return false;
}
unsigned QDate::daysInYear(unsigned nYear)
{
	return leapYear(nYear) ? 366 : 365;
}
double QDate::BasisDaysBetween(const QDate& tStartDate, const QDate& tEndDate, EAccrualBasis eAccrualBasis)
{
	if (tStartDate > tEndDate)throw"Error:startDate > endDate!!!";

	double dDaysBetween(0);
	unsigned int nStartMonth=tStartDate.Month(), nStartYear= tStartDate.Year(),dStartDay = tStartDate.Day();

	unsigned int nEndMonth=tEndDate.Month(), nEndYear=tEndDate.Year(),dEndDay=tEndDate.Day();

	switch (eAccrualBasis)
	{
		case (EAccrualBasis::e_30360):
			//1.start的day必须满足<= 30
			//2.end的day = 31 时
			//		情形1：start的day >= 30,则end的day为30
			//		情形2：start的day < 30，则end的day为31.
			if (dStartDay >= 30 && dEndDay == 31) dEndDay--;
			if (dStartDay == 31) dStartDay--;
			dDaysBetween = 360 * (nEndYear - nStartYear)+ 30 * (nEndMonth - nStartMonth)+ (dEndDay - dStartDay);
			break;
		case (EAccrualBasis::e_30E360)://start,end的day必须满足<=30
			if (dStartDay == 31) dStartDay--;
			if (dEndDay == 31) dEndDay--;
			dDaysBetween = 360 * (nEndYear - nStartYear)+ 30 * (nEndMonth - nStartMonth)+ (dEndDay - dStartDay);
			break;
		case (EAccrualBasis::e_Act360):
		case (EAccrualBasis::e_Act365):
		case (EAccrualBasis::e_ActAct):
		case (EAccrualBasis::e_Act29):
			dDaysBetween = tEndDate - tStartDate;
			break;
		case (EAccrualBasis::e_Coupon):
			throw("BasisDaysBetween: Invalid concept for this basis (%d)", (int)eAccrualBasis);
			break;
		default:
			throw("BasisDaysBetween: Invalid basis (%d)", (int)eAccrualBasis);
	}

	return dDaysBetween;
}
unsigned QDate::daysInMonthYear(unsigned nMonth, unsigned nYear)
{
	unsigned d = monthDay[nMonth];

	if (leapYear(nYear)==false && nMonth == 2) d--;

	return d;
}
int QDate::BusinessDaysBetween(const QDate& tStartDate, const QDate& tEndDate)
{
	QDate tDateCounter(tStartDate);
	int nBusinessDays(0);

	for (; tDateCounter < tEndDate; tDateCounter++)
	{
		if (tDateCounter.isBusinessDay())
		{
			nBusinessDays++;
		}
	}

	return nBusinessDays;
}

int QDate::BasisDaysInYear(EAccrualBasis eAccrualBasis, int nYear)
{
	switch (eAccrualBasis)
	{
		case (EAccrualBasis::e_30360):
		case (EAccrualBasis::e_30E360):
		case (EAccrualBasis::e_Act360):
			return 360;
		case (EAccrualBasis::e_Act365):
			return 365;
		case (EAccrualBasis::e_ActAct):
		case (EAccrualBasis::e_Act29):
		case (EAccrualBasis::e_Coupon):
			return daysInYear(nYear);
		default:
			throw("BasisDaysInYear: Invalid basis (%d)", (int)eAccrualBasis);
			return 0;
	}
}
int QDate::getNumofMEs(int begDate, int endDate)//两个日期之间有几个月末(包括首尾日期)
{
	int nm = 0;
	GetNumMonthEnds(begDate, endDate, nm);
	return nm;
}
int QDate::getNumofMEs(int endDate)
{
	int nm = 0;
	GetNumMonthEnds(ExcelDay, endDate, nm);
	return nm;
}
int QDate::DaysOfYear()
{
	if (isleap())return 366;
	else return 365;

}

ostream& operator<<(ostream& os, const QDate& tThis)
{
	os << tThis.dateToString();//因为tThis是const变量，所以该变量调用的成员函数必须为const类型的成员函数
	return os;
}
istream& operator>>(istream& is, QDate& tThis)
{
	string strBuffer;
	getline(is, strBuffer);
	tThis = QDate(strBuffer.c_str());
	return is;
}
QDate plusSpan(const QDate& tThis, const QDateSpan& qThat)
{
	QDate tNewDate(tThis);

	tNewDate += qThat;

	return tNewDate;
}
//QDate operator+(const QDate& tThis, double dOffset)
//{
//	return QDate(tThis.getExcelDay() + int(dOffset));
//}
QDate minusSpan(const QDate& tThis, const QDateSpan& qThat)
{
	QDate tNewDate(tThis);
	tNewDate -= qThat;
	return tNewDate;
}


//Array1I QDate::DayVectorBetween(QDate another_date,const ArrayDate1& day_vector) {
//
//	QDate start, end;//默认构造函数
//	if (ExcelDay < another_date.getExcelDay())
//	{
//		start = *this;//复制重载
//		end = another_date;
//	}
//	else if (ExcelDay > another_date.getExcelDay())
//	{
//		end = *this;//复制重载
//		start = another_date;
//	}
//	else
//		throw "The same beg & end date!!!";
//
//	int starting_index(-1);
//	int ending_index(-1);
//
//	Array1I start_search_result = BinarySearch(start,day_vector);
//	if (start_search_result[0]) {
//		// if found
//		starting_index = start_search_result[1];
//	}
//	else {
//		// not found
//		starting_index = start_search_result[1] + 1;
//	}
//
//	Array1I end_search_result = BinarySearch(end,day_vector);
//	ending_index = end_search_result[1];
//	if (ending_index < starting_index) {
//		// Error
//		//"Error in DayVectorBetween, no valid days between" 
//
//		starting_index = -1;
//		ending_index = -1;
//	}
//
//	Array1I result(2); result[0] = starting_index; result[1] = ending_index;
//	return result;
//}


//============================================修改来自于RMI中的函数========================
//Array1I BinarySearch(const QDate& qd0, const ArrayDate1& date_vector, int starting_position = 0);
//Array1I BinarySearch(const QDate& qd0, const tvec<QDate>& date_vector, int starting_position = 0);
Array1I BinarySearch(const QDate& qd0, const ArrayDate1& date_vector, int starting_position)
{
	/* Search for *this in the date_vector in a binary way.
	The search starts from the starting_position
	If found, return true and the index of the element in date_vector.
	If not found, return false and the index of the largest index
		smaller than *this.
	date_vector needs to be sorted.
	If *this is smaller than the smallest element of date_vector,
		return false and starting_position.
	*/

	//如果在数组中找到相应日期：返回{1,index0}.前者表示true,后者表示找到的index0
	//如果在数组中未找到相应日期：返回{0，index0}.前者表示false,后者表示早于该日期的最大index0
	int first_index = starting_position;
	int last_index;
	last_index = static_cast<int>(date_vector.size() - 1);

	Array1I result(2); result[0] = 0; result[1] = 0;
	bool found = false;
	if (qd0 < date_vector[first_index])
	{
		//"warning in binary_search: index out of range" 
		result[0] = 0; result[1] = first_index;
		return result;
	}
	else if (qd0 > date_vector[last_index])
	{
		//"warning in binary_search: index out of range" 
		result[0] = 0; result[1] = last_index;
		return result;
	}
	int mid_point=0;
	while (first_index <= last_index && (!found))
	{
		mid_point = (first_index + last_index) / 2;
		if (qd0 == date_vector[mid_point])
		{
			found = true;
			result[0] = 1; result[1] = mid_point;
			return result;
		}
		else if (qd0 < (date_vector)[mid_point])
		{
			last_index = mid_point - 1;
		}
		else
		{
			first_index = mid_point + 1;
		}
	}
	while (qd0 < (date_vector)[mid_point]) {
		mid_point = mid_point - 1;
	}
	result[0] = 0; result[1] = mid_point;
	return result;
}
Array1I BinarySearch(const QDate& qd0, const tvec<QDate>& date_vector, int starting_position)
{
	/* Search for *this in the date_vector in a binary way.
	The search starts from the starting_position
	If found, return true and the index of the element in date_vector.
	If not found, return false and the index of the largest index
		smaller than *this.
	date_vector needs to be sorted.
	If *this is smaller than the smallest element of date_vector,
		return false and starting_position.
	*/

	//如果在数组中找到相应日期：返回{1,index0}.前者表示true,后者表示找到的index0
	//如果在数组中未找到相应日期：返回{0，index0}.前者表示false,后者表示早于该日期的最大index0
	int first_index = starting_position;
	int last_index;
	last_index = static_cast<int>(date_vector.n - 1);

	Array1I result(2); result[0] = 0; result[1] = 0;
	bool found = false;
	if (qd0 < date_vector[first_index])
	{
		//"warning in binary_search: index out of range" 
		result[0] = 0; result[1] = first_index;
		return result;
	}
	else if (qd0 > date_vector[last_index])
	{
		//"warning in binary_search: index out of range" 
		result[0] = 0; result[1] = last_index;
		return result;
	}
	int mid_point;
	while (first_index <= last_index && (!found))
	{
		mid_point = (first_index + last_index) / 2;
		if (qd0 == date_vector[mid_point])
		{
			found = true;
			result[0] = 1; result[1] = mid_point;
			return result;
		}
		else if (qd0 < (date_vector)[mid_point])
		{
			last_index = mid_point - 1;
		}
		else
		{
			first_index = mid_point + 1;
		}
	}
	while (qd0 < (date_vector)[mid_point]) {
		mid_point = mid_point - 1;
	}
	result[0] = 0; result[1] = mid_point;
	return result;
}
double Accrual(int date1, int date2, quantEnum basis)
{

	switch (basis) {
	default: break;
	case quantEnum::basis_1_1_y:
		return 1.0;
	case quantEnum::basis_1_2_y:
		return 0.5;
	case quantEnum::basis_1_4_y:
		return 0.25;
	case quantEnum::basis_30E_360:
		return accrued_30(date1, date2, 1) / 360.0;
	case quantEnum::basis_30_360:
		return accrued_30(date1, date2, 0) / 360.0;
	case quantEnum::basis_actual_360:
		return (date2 - date1) / 360.0;
	case quantEnum::basis_actual_365:
		return (date2 - date1) / 365.0;
	case quantEnum::basis_actual_actual: {
		double	acc = 0;
		int		y1, m1, d1;
		int		y2, m2, d2, y;
		Day2YMD(date1, &y1, &m1, &d1);
		Day2YMD(date2, &y2, &m2, &d2);
		for (y = y1; y <= y2; y++) {
			int		yearStart = YMD2Day(y - 1, 12, 31);
			int		yearEnd = YMD2Day(y, 12, 31);
			int		dt1 = MAX(date1, yearStart);
			int		dt2 = MIN(yearEnd, date2);
			double	dpy = ISLEAP(y) ? 366.0 : 365.0;
			acc += (dt2 - dt1) / dpy;
		}
		return acc;
	}
	}
	return 0;
}
double Accrual(const QDate& date1, const QDate& date2, quantEnum basis)
{
	return Accrual(date1.getExcelDay(), date2.getExcelDay(), basis);
}
ArrayDate1 DateVectorBuilder(const QDate& one_date, const QDate& another_date, quantEnum frequency, bool biz_day_adjust)
{
	// build a vector of date with a given frequency.


	QDate start, end;//默认构造函数
	if (one_date.getExcelDay() < another_date.getExcelDay())
	{
		start = one_date;//复制重载
		end = another_date;
	}
	else if (one_date.getExcelDay() > another_date.getExcelDay())
	{
		end = one_date;//复制重载
		start = another_date;
	}
	else
		throw "The same beg & end date!!!";

	tvec<QDate> dates;//可使用resize,而不改变原来容器中的值

	if (frequency == quantEnum::daily) {
		// In case of frequency is daily, the original algorithm produces repeated dates
		if (start.isHoliday()) start = start.FBD_date();

		while (start <= end)
		{
			size_t m = dates.n;//原来的长度
			dates.resize(m + 1);
			dates[m] = start;
			start = (start + 1).FBD_date();
		}
	}
	else
	{
		int step = 1;
		char unit = 'd';
		if (frequency == quantEnum::weekly) { step = 1; unit = 'w'; }
		else if (frequency == quantEnum::monthly) { step = 1; unit = 'm'; }
		else if (frequency == quantEnum::quarterly || frequency == quantEnum::quarter) { step = 3; unit = 'm'; }
		else if (frequency == quantEnum::annually || frequency == quantEnum::annual) { step = 1; unit = 'y'; }//后者在IRS中的表示
		else if (frequency == quantEnum::maturity) { step = end.getExcelDay() - start.getExcelDay(); unit = 'd'; }
		else throw"unrecognized frequency";

		int multiplier = 1;
		if (start.isHoliday()) start = start.FBD_date();
		while (start <= end)
		{
			size_t m = dates.n;//原来的长度
			dates.resize(m + 1);
			dates[m] = start;
			start = start.AddPeriod(step * multiplier, unit, biz_day_adjust);;
		}
	}

	// ending date is appended to the vector
	if (dates[dates.n - 1] != end)
	{
		dates.resize(dates.n + 1);
		dates[dates.n - 1] = end;
	}

	ArrayDate1 date_arr;
	date_arr.resize(dates.n);
	for (int i = 0; i < dates.n; i++)
		date_arr[i] = dates[i];


	return date_arr;
}
ArrayDate1 biz_day_between(const QDate& beg_t, const QDate& end_t)
{
	tvec<QDate> dates;
	QDate temp_t = beg_t;
	while (temp_t <= end_t)
	{
		if (temp_t.isHoliday() == false)dates.push_back(temp_t);
		temp_t = temp_t + 1;
	}
	ArrayDate1 QDarr(dates.n);
	for (int i = 0; i < dates.n; i++)
		QDarr[i] = dates[i];
	return QDarr;
}


//================================================以下函数，已添加至class中去==============
// Convert excel day number to YMD.
void Day2YMD(int day, int* yy, int* mm, int* dd) {
	int		d1 = day - EXCEL_OFFSET;		// Convert to days since 1900.
	int		d2 = d1 + DAYS(1900) - 31 - 28;	// Days since Feb year 0.
	int		y0 = (int)(d2 / 365.25);		// Possible years since feb 0.
	int		y1 = y0 + 1;					// Possible years since feb 0.
	int		y2 = DAYS(y1) <= d2 ? y1 : y0;	// Choose correct year.  Will breakdown around year 365*400/3.
										// Tested to year 10000 it seems OK.
	int		d3 = d2 - DAYS(y2);				// Days since feb y2.
	int		m;

	// Search for month number.
	for (m = 0; m < 12; m++) if (d3 < monthCum[m + 1]) break;

	// Adjust results for year starting on Jan 1st.
	if (yy) (*yy) = y2 + (d3 < 365 - 31 - 28 ? 0 : 1);
	if (mm) (*mm) = (m + 2) % 12 + 1;
	if (dd) (*dd) = d3 - monthCum[m] + 1;
}
// Convert YMD to excel day number
int YMD2Day(int yy, int mm, int dd) {
	int		d1 = dd - 1;					// Convert to 1st day of month is day 0.
	int		m1 = (mm - 1 + 10) % 12;			// Convert to march is month 0.
	int		y1 = yy - (m1 < 10 ? 0 : 1);		// Convert to years since feb year 0.
	int		d2 = 31 + 28 +					// Days before feb 1900.
		DAYS(y1) - DAYS(1900) +	// Days from feb 1900 to feb y1.
		monthCum[m1] +			// Month days.
		d1;						// Days.
	int		d3 = d2 + EXCEL_OFFSET;			// Allow for Excel date convention.
	return d3;
}
// Add months to date.
int addMonth(int date, int months) {
	int	yy, mm, dd;
	Day2YMD(date, &yy, &mm, &dd);
	int	d1 = dd;
	int	m1 = mm - 1 + months;			// Months (jan=0);
	int	m2 = (m1 % 12 + 12) % 12 + 1;		// Months+m (jan=1)
	int	dy = m1 / 12;				// Number of years to add.
	if (m2 != 1 && m1 < 0) dy--;	// Truncate m1/12 towards -infinity.
	int	y1 = yy + dy;
	if (d1 > monthDay[m2]) d1 = monthDay[m2];	// Don't exceed days per month.
	if (y1 % 4 != 0 || y1 % 100 == 0 && y1 % 400 != 0) {
		if (m2 == 2 && d1 > 28) d1 = 28;			// Don't feb 28 unless leap year.
	}
	int	dt2 = YMD2Day(y1, m2, d1);
	return dt2;
}

int addYear(int date, int dy)
{
	int	yy, mm, dd;
	Day2YMD(date, &yy, &mm, &dd);
	int	d1 = dd;
	int	m1 = mm;			// Months (jan=0);
	int	y1 = yy + dy;
	if (y1 % 4 != 0 || y1 % 100 == 0 && y1 % 400 != 0) {
		if (m1 == 2 && d1 > 28) d1 = 28;			// Don't feb 28 unless leap year.
	}
	int	dt2 = YMD2Day(y1, m1, d1);
	return dt2;

}
// Get EndOfMonth date from months added to date.
int monthEnd(int date, int months) {
	int	yy, mm, dd;
	Day2YMD(date, &yy, &mm, &dd);
	int	d1 = dd;
	int	m1 = mm - 1 + months;			// Months (jan=0);
	int	m2 = (m1 % 12 + 12) % 12 + 1;		// Months+m (jan=1)
	int	dy = m1 / 12;				// Number of years to add.
	if (m2 != 1 && m1 < 0) dy--;	// Truncate m1/12 towards -infinity.
	int	y1 = yy + dy;
	d1 = monthDay[m2];	// Set to last days of the month.
	if (y1 % 4 != 0 || y1 % 100 == 0 && y1 % 400 != 0)
	{
		if (m2 == 2 && d1 > 28) d1 = 28;			// Don't feb 28 unless leap year.
	}
	int	dt2 = YMD2Day(y1, m2, d1);
	return dt2;
}
// Return 1 if dt is a holiday (or weekend).
int isHol(int dt, int n, const int* hol) {
	int	dt2 = dt % 7;
	int	j;
	switch (dt2) {
	case 0:		// Saturday.
	case 1:		// Sunday.
		return 1;
	default:
		BSRCH(n, hol, dt, j);
		if (j < 0) return 0;	// Not in list of holidays.
		return 1;
	}
}
int workDay(
	int				date,
	int				days,	// Number of days to add to date.
	int				n1,		// Number of holidays.
	const int* hol) {	// Vector of holiday dates.

	int	dir = days < 0 ? -1 : 1;
	int	dt = date;
	for (; isHol(dt, n1, hol); dt += dir);			// Move to working day.

	int	ndy = days < 0 ? -days : days;
	while (0 < ndy) {							// Step through working days.
		dt += dir;							// Step to next day.
		for (; isHol(dt, n1, hol); dt += dir);		// Move to working day.
		ndy--;
	}

	return dt;
}
// Use Modified Following rule to find corresponding business day,
int MFBD(int date, int nHol, const int* hol) {
	int	dt;
	for (dt = date; isHol(dt, nHol, hol); dt++);		// Move to next working day.

	int	y1, m1, d1;
	int	y2, m2, d2;
	Day2YMD(date, &y1, &m1, &d1);
	Day2YMD(dt, &y2, &m2, &d2);
	if (m1 == m2) return dt;						// Next working day in correct month.

	for (dt = date; isHol(dt, nHol, hol); dt--);		// Move to previous working day.
	return dt;
}
int MFBD(int date) { return MFBD(date, 0, 0); }
int MPBD(int date, int nHol, const int* hol) {
	int	dt;
	for (dt = date; isHol(dt, nHol, hol); dt--);		// Move to previous working day.

	int	y1, m1, d1;
	int	y2, m2, d2;
	Day2YMD(date, &y1, &m1, &d1);
	Day2YMD(dt, &y2, &m2, &d2);
	if (m1 == m2) return dt;						// Next working day in correct month.

	for (dt = date; isHol(dt, nHol, hol); dt++);		// Move to next working day.
	return dt;
}

// Original code supplied by G. Vass 19 Oct 99, in files aegisDaycount.cpp & aegisBusiness.cpp:
int accrued_30(int date1, int date2, int Eflag) {
	int		y1, m1, d1, dt1 = date1;
	int		y2, m2, d2, dt2 = date2;
	Day2YMD(date1, &y1, &m1, &d1);
	Day2YMD(date2, &y2, &m2, &d2);
	if (d1 == 31) { dt1--; d1 = 30; }
	//d1最多为30
	if (d2 == 31 && (Eflag || d1 == 30)) { dt2--; d2 = 30; }
	//30E-360时：Eflag = 1. ——>d2最多为30
	// 30-360时：Eflag = 0. --->d2可能为31. 此时d2原先为31并且d1 原先<30.
	// 
	//Eflag=0:30-360 bond basis                       d2可能等于31
	//Eflag=1:30E-360 Eurobond    &&后面肯定成立，     d2最多为30
	return (y2 - y1) * 360 + (m2 - m1) * 30 + (d2 - d1);
}



// returns number of Month ends between given dates
void GetNumMonthEnds(int sDate, int eDate, int& nMonths)
{
	if (eDate < sDate)
	{
		int temp = sDate;
		sDate = eDate;
		eDate = temp;
	}

	int rollDate = sDate;
	nMonths = 2; //includes start and end date

	while (monthEnd(rollDate + 1, 0) < eDate && nMonths < 1200) //1200 = 100 yrs on months
	{
		rollDate = monthEnd(rollDate + 1, 0);//第二天开始的这个月的最后一天
		rollDate += 1; //increment one day into next month//再加一天，那么rollDate是下个月的第一天
		++nMonths;
	}
}
int deltaYears(QDate& d1, QDate& d2)//d1-d2的年份数
{

	QDate minDate, maxDate;
	if (d1 <= d2) {
		minDate = d1; maxDate = d2;
	}
	else
	{
		minDate = d2; maxDate = d1;
	}

	int delta = 0;
	if (maxDate.getExcelDay() - minDate.getExcelDay() < minDate.DaysOfYear()) delta = 0;
	else
	{
		delta = 1;
		QDate d0 = maxDate.MinusPeriod(delta, 'Y', false);
		while (d0.getExcelDay() - minDate.getExcelDay() >= minDate.DaysOfYear())
		{
			delta++;
			d0 = maxDate.MinusPeriod(delta, 'Y', false);
		}
	}
	if (d1 <= d2) return -1 * delta;
	else return delta;
}
int deltaMonths(QDate& d1, QDate& d2)//d1-d2的月份数，只比较月份
{

	int m1 = d1.Month(), m2 = d2.Month();
	int day1 = d1.Day(), day2 = d2.Day();

	if (m1 == m2) return 0;
	else
	{
		if (m1 > m2)//>=0
		{
			if (day1 >= day2) return m1 - m2;
			else if (day1 < day2 && day1 == lastDayInMonth(d1)) return m1 - m2;
			else return m1 - m2 - 1;
		}
		else//<=0
		{
			if (day1 <= day2) return m1 - m2;
			else if (day1 > day2 && day2 == lastDayInMonth(d2)) return m1 - m2;
			else return m1 - m2 + 1;
		}
	}
}
int lastDayInMonth(QDate& d)
{
	int m = d.Month();
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) return 31;
	else if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
	else
	{
		if (d.isleap()) return 29;
		else return 28;
	}

}



//================================================以下函数，暂未添加至class中去==============
// returns number of Month ends between given dates and vector of MonthEnd Dates
//void GetNumMonthEnds(int sDate, int eDate, int& nMonths, vector<int>& MonthDates)
//{
//		if(eDate < sDate)
//		{
//		int temp=sDate;
//		sDate=eDate;
//		eDate=temp;
//		}
//		
//		int rollDate=sDate;
//		nMonths=2;
//		MonthDates.push_back(rollDate);
//
//		while(monthEnd(rollDate+1,0) < eDate && nMonths < 1200) //1200 = 100 yrs on months
//		{
//		rollDate=monthEnd(rollDate+1,0);
//		MonthDates.push_back(rollDate);
//
//		rollDate+=1; //increment one day into next month
//		++nMonths;	
//		}
//
//		MonthDates.push_back(eDate); // add end date
//}
//
//
//
//
//// Validate holidays.
//const char *holsOK(
//	int				n1,		// Number of holidays.
//	const int		*hol) {	// Vector of holiday dates.
//
//	if (n1 < 0) {
//		const char* s = " Negative number of holidays"; return s;
//	}
//	if (!hol) {
//		if (0 < n1) {
//			const char* s = " Invalid holidays"; return s;
//		}
//		return 0;
//	}
//	int	i;
//	for(i=1;i<n1;i++)
//		if (hol[i] <= hol[i - 1])
//		{
//			const char* s = " Holidays must be in ascending order without duplicates"; return s;
//		}
//	return 0;
//}


