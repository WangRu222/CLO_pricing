#include <iostream>
#include <fstream>//
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <vector>
#include "date.h"

using namespace std;
using namespace boost::numeric::ublas;//使用boost中的matrix

enum class CLO_Tranche {
	NotSet = -1,
	equity_Tranche = 0,
	senior_Tranche_1 = 1,
	senior_Tranche_2 = 2,
	senior_Tranche_3 = 3,
	senior_Tranche_4 = 4,
};
enum class CLO_Coupon_Frequency {
	notSet = 0,
//这里如果有些特殊情况，譬如少见的15天等，就另使用paygap=24;这个值在每次应该根据数据情况进行重新赋值
	monthly = 12,//一年支付的次数
	quarterly = 4,
	semiannually = 2,
	annually = 1,
	paygap =24,
};

class CLO
{
public:
	/*
		构造函数中存储属于资产端的相关数据:
		1. 优先级和次级所有tranche的个数
		2. 各个tranche的coupon序列， 因为对于某个trache定价，通常依赖所有tranche的coupons,所以作为构造函数变量传递进来
		3. 估值日期
		4. 0早偿0违约的资产端数据数据
	*/

	//obtain the asset cash flow from csv file;
	CLO(
		//基本参数
		size_t _N_of_Senior, //优先级级数
		size_t _N_of_Equity, //次级级数
		QDate _valuationDate,//估值日期

		//证券端相关参数
		std::vector<double> _coupon, //各tranche的coupon 票面利率
		std::vector<double> _tranche_notional, //各tranche的期末本金
		QDate _last_coupon_date, //各tranche上一个付息日期
		QDate _next_coupon_date, //各tranche下一个付息日期
		CLO_Coupon_Frequency _coupon_frequency,//各tranche的coupon支付频率

		//影响证券端分配的参数
		double _tax_ratio,//税费比例
		//bool _pay_couponToEquityTranche_beforeEndofSeniorTranche, //优先级结束前是否支付次级利息
		double _award_ratio,//次级结束后支付的奖励比例
		

		//原始资产端数据
		string _infile_csvName);

	//obtain the asset cash flow from vector of vector
	CLO(
		//基本参数
		size_t _N_of_Senior, 
		size_t _N_of_Equity, 
		QDate _valuationDate,

		//证券端相关参数
		std::vector<double> _coupon,  //各tranche的coupon
		std::vector<double> _tranche_notional, //各tranche的期末本金
		QDate _last_coupon_date, //各tranche上一个付息日期
		QDate _next_coupon_date, //各tranche下一个付息日期
		CLO_Coupon_Frequency _coupon_frequency,//各tranche的coupon支付频率

		//影响证券端分配的参数
		double _tax_ratio,//税费比例
		//bool _pay_couponToEquityTranche_beforeEndofSeniorTranche, //优先级结束前是否支付次级利息
		double _award_ratio,//次级结束后支付的奖励比例

		//原始资产端数据
		std::vector<std::vector<double>> _original_AssetCF
		);



	//choose the tranche need to value
	void set_tranche(CLO_Tranche _tranche);

	//set paras which determin the asset cash flow
	void set_AssetCF_paras(double _CPR, double _DR, double _LGD, double _Default_Ratio);
	void set_TrancheCF_paras(double _tax, double _award_after_EndofEquity);

	//obtain the Asset notional and Asset interest in the future with 0 CPR & 0 Default
	//the original data from report
	void set_Original_AssetCF();
	void update_AssetCF();//产生更新后的资产端数据
	void update_TrancheCF();//产生更新后的证券端数据

	void generate_dates_TrancheCF();
	void set_yld(double _yld);//根据到期收益率计算各期贴现因子
	void calculate();//根据资产端现金流及贴现因子; 计算净价，全价，应计利息等数据；
	void calculate_wind(int _tranche_index, string _trancheCF_csvName, std::vector<double> _results);//基于wind给定的证券端数据直接贴现，计算价格; tranche_index从1开始
	void calculate_wind(int _tranche_index, std::vector<std::vector<double>> _trancheCF_vector, std::vector<double> _results);//基于wind给定的证券端数据直接贴现，计算价格;tranche_index从1开始
	void get_price(std::vector<double>& _dirty_price, std::vector<double>& _clean_price, std::vector<double>& _accrued_interest);//获取估值信息


private:

	/*资产池固有的属性*/
	double notional;//资产端期末本金余额
	size_t N_of_Senior;//优先证券级数
	size_t N_of_Equity;//次级证券级数
	//frequency poolAsset_frequency;//资产池资产付息频率，可能并不是始终不变； 如22建鑫9优先级结束前为半年一次；优先级结束之后为3月一次；
	std::vector<double> coupon;//size必需等于N_of_Senior+N_of_Equity; 证券端票息率
	std::vector<double> tranche_notional; //各tranche的期末本金
	std::vector<double>  ; //截止估值日,各tranche的累计应付利息
	QDate valuationDate;//估值日期
	QDate lastDate; //上一个资产端现金流流入日期
	QDate nextDate; //下一个资产端现金流流入日期
	QDate last_coupon_date;//上一个tranche付息日
	QDate next_coupon_date;//下一个tranche付息日
	CLO_Coupon_Frequency coupon_frequency;//tranche端付息频率
	//bool pay_couponToEquityTranche_beforeEndofSeniorTranche; //优先级结束前是否支付次级利息


	/*决定资产端现金流的相关参数*/
	double CPR;//年化早偿率 
	//double SMM;//每一期的早偿率
	/*SMM与CPR的关系:
		一年分12期：1 + CPR = (1 + SMM)^12
		一年分4期： 1 + CPR = (1 + SMM)^4
		一般情形：  1 + CPR = (1 + SMM)^(365/days)
	*/
	double DR; //年化违约率
	double LGD;//违约损失率
	double Default_Ratio;//当期收回部分违约概率/未来收回部分违约概率
	size_t N_of_AssetCF;//资产端现金流期数
	double yld;//定价用的到期收益率

	/*确定证券端属性*/
	CLO_Tranche tranche;//当前证券级别
	/*影响证券端分配的部分参数*/
	double tax_ratio;//偿付税费费用比率; 年化税费比例
	double award_ratio;//次级证券结束之后, 资产端现金流理论上均作为次级证券的收益返回给次级证券持有者；可能设置一个award先给贷款机构

	/*资产端相关序列数据*/
	std::vector<int> dates_AssetCF;//资产端现金流日期序列
	std::vector<std::vector<double>> original_AssetCF;//0早偿0违约资产端现金流
	std::vector<std::vector<double>> updated_AssetCF;//根据早偿率和违约率更新后的资产端现金流
	/*考虑早偿因素后得到的相关数据*/
	std::vector<double> retrive_notional_CPR;//考虑早偿因素后的,实际收回本金
	std::vector<double> retrive_interest_CPR;//考虑早偿因素后的,实际收回利息(wind目前早偿因素对interest没有影响)
	std::vector<double> periodEnd_notional_CPR;//考虑早偿因素的每期期末本金余额
	std::vector<double> periodEnd_cashflow_CPR;//考虑早偿因素的每期期末资产端现金流（包括收回利息+收回本金）
	std::vector<double> CPR_amount;//每期早偿金额
	/*考虑违约因素后得到的相关数据*/
	std::vector<double> retrive_notional_DR;//考虑违约因素后的,实际收回本金
	std::vector<double> retrive_interest_DR;//考虑违约因素后的,实际收回利息
	std::vector<double> periodEnd_notional_DR;//考虑违约因素的每期期末本金余额
	std::vector<double> periodEnd_cashflow_DR;//考虑违约因素的每期期末资产端现金流（包括收回利息+收回本金）
	std::vector<double> DR_amount;//每期违约金额

	/*证券端相关序列数据*/
	std::vector<int> dates_TrancheCF;//证券端现金流日期序列, 产生的序列长度默认等于资产端长度; 通常不会用到这么长的序列
	std::vector<double> tax_amount;//每期税费扣除
	std::vector<double> dfs;//与证券端数组长度一致的，贴现因子序列
	std::vector<std::vector<double>> retrive_interest_TrancheCF;//外层size() == tranche个数
	std::vector<std::vector<double>> retrive_notional_TrancheCF;//外层size() == tranche个数
	std::vector<std::vector<double>> periodEnd_notional_TrancheCF;//外层size() == tranche个数
	std::vector<std::vector<double>> periodEnd_cashflow_TrancheCF;//外层size() == tranche个数

	/*来源于wind的证券端数据*/
	std::vector<double> wind_trancheCF;//来源于wind的证券端数据，用于直接根据wind现金流计算wind的价格; cash flow = notional + interest

	/*CLO价格*/
	std::vector<double> dirty_price;//size() == tranche个数
	std::vector<double> clean_price;//size() == tranche个数
	std::vector<double> accrued_interest;//size() == tranche个数
	
};

CLO::CLO(		//基本参数
	size_t _N_of_Senior, //优先级级数
	size_t _N_of_Equity, //次级级数
	QDate _valuationDate,//估值日期
	//证券端相关参数
	std::vector<double> _coupon, //各tranche的coupon
	std::vector<double> _tranche_notional, //各tranche的期末本金
	QDate _last_coupon_date, //各tranche上一个付息日期
	QDate _next_coupon_date, //各tranche下一个付息日期
	CLO_Coupon_Frequency _coupon_frequency,//各tranche的coupon支付频率
	//影响证券端分配的参数
	double _tax_ratio,//税费比例
	//bool _pay_couponToEquityTranche_beforeEndofSeniorTranche, //优先级结束前是否支付次级利息
	double _award_ratio,//次级结束后支付的奖励比例
	//原始资产端数据
	string _infile_csvName):
	N_of_Senior(_N_of_Senior), N_of_Equity(_N_of_Equity), valuationDate(_valuationDate),
	coupon(_coupon), tranche_notional(_tranche_notional),
	last_coupon_date(_last_coupon_date),next_coupon_date(_next_coupon_date), coupon_frequency(_coupon_frequency),
	tax_ratio(_tax_ratio), award_ratio(_award_ratio)
{
	if (_N_of_Senior <= 0 || _N_of_Senior >3 || _N_of_Equity != 1)throw"Cannot deal with CLO of this structure!";
	if (_coupon.size() != _N_of_Senior + _N_of_Equity)throw"Size of Coupons must equal to number of tranches!";

	//=============从csv文件中获取0早偿0违约资产端现金流用于定价===============
	original_AssetCF.clear();
	updated_AssetCF.clear();

	ifstream infile(_infile_csvName.c_str(), ios::in);
	if (!infile.is_open())
	{
		cout << "Error: opening file failed" << endl;
		exit(1);
	}
	string line;
	istringstream sin;
	while (getline(infile, line))
	{
		std::vector<double> temp;
		sin.clear();
		sin.str(line);
		string s0;
		while (getline(sin, s0, ','))
		{
			temp.push_back(stod(s0)); //cout << stod(s0) << ",";
		}
		original_AssetCF.push_back(temp);
		updated_AssetCF.push_back(temp);
	}
	infile.close();
	set_Original_AssetCF();
	//=============从csv文件中获取0早偿0违约资产端现金流用于定价===============

	//以下参数从set_AssetCF_paras函数中获得
	CPR = 0.0;
	DR = 0.0;
	LGD = 0.0;
	Default_Ratio = 0;

	//以下参数从set_tranche函数中获得
	tranche = CLO_Tranche::NotSet;

}

CLO::CLO(		//基本参数
	size_t _N_of_Senior,
	size_t _N_of_Equity,
	QDate _valuationDate,

	//证券端相关参数
	std::vector<double> _coupon,
	std::vector<double> _tranche_notional, //各tranche的期末本金
	QDate _last_coupon_date, //各tranche上一个付息日期
	QDate _next_coupon_date, //各tranche下一个付息日期
	CLO_Coupon_Frequency _coupon_frequency,//各tranche的coupon支付频率
	//影响证券端分配的参数
	double _tax_ratio,//税费比例
	//bool _pay_couponToEquityTranche_beforeEndofSeniorTranche, //优先级结束前是否支付次级利息
	double _award_ratio,//次级结束后支付的奖励比例
	//原始资产端数据
	std::vector<std::vector<double>> _original_AssetCF) :
	N_of_Senior(_N_of_Senior), N_of_Equity(_N_of_Equity), valuationDate(_valuationDate),
	coupon(_coupon), tranche_notional(_tranche_notional),
	last_coupon_date(_last_coupon_date), next_coupon_date(_next_coupon_date), coupon_frequency(_coupon_frequency),
	tax_ratio(_tax_ratio), award_ratio(_award_ratio),
	original_AssetCF(_original_AssetCF),updated_AssetCF(_original_AssetCF)
{
	if (_N_of_Senior <= 0 || _N_of_Senior > 3 || _N_of_Equity != 1)throw"Cannot deal with CLO of this structure!";
	if (_coupon.size() != _N_of_Senior + _N_of_Equity)throw"Size of Coupons must equal to number of tranches!";

	//=============从vector变量中获取0早偿0违约资产端现金流用于定价===============
	set_Original_AssetCF();
	//=============从vector变量中获取0早偿0违约资产端现金流用于定价===============
	
	//以下参数从set_AssetCF_paras函数中获得
	CPR = 0.0;
	DR = 0.0;
	LGD = 0.0;
	Default_Ratio = 0;

	//以下参数从set_tranche函数中获得
	tranche = CLO_Tranche::NotSet;
}

void CLO::set_tranche(CLO_Tranche _tranche)
{
	tranche = _tranche;
}
void CLO::set_AssetCF_paras(double _CPR, double _DR, double _LGD, double _Default_Ratio)
{
	if (_CPR > 0)CPR = _CPR;
	else CPR = 0.0;
	DR = _DR;
	LGD = _LGD;
	Default_Ratio = _Default_Ratio;

}
void CLO::set_TrancheCF_paras(double _tax, double _award_after_EndofEquity)
{

}
void CLO::set_Original_AssetCF()
{
	if (original_AssetCF.size() >= 2 && original_AssetCF[0].size() == 4 && original_AssetCF[1].size() == 4)
	{
		lastDate = original_AssetCF[0][0];
		nextDate = original_AssetCF[1][0];
		notional = original_AssetCF[0][3];
		N_of_AssetCF = original_AssetCF.size();
		dates_AssetCF.resize(N_of_AssetCF);
		for (int i = 0; i < N_of_AssetCF; ++i)dates_AssetCF[i] = original_AssetCF[i][0];//存储日期序列

		//存储早偿影响后的资产端数据
		retrive_notional_CPR.resize(N_of_AssetCF);
		retrive_interest_CPR.resize(N_of_AssetCF);
		periodEnd_notional_CPR.resize(N_of_AssetCF);
		periodEnd_cashflow_CPR.resize(N_of_AssetCF);
		CPR_amount.resize(N_of_AssetCF);

		retrive_notional_CPR[0] = 0.0;
		retrive_interest_CPR[0] = 0.0;
		periodEnd_notional_CPR[0] = original_AssetCF[0][3];
		periodEnd_cashflow_CPR[0] = 0.0;
		CPR_amount[0] = 0.0;

		//存储违约影响后的资产端数据
		retrive_notional_DR.resize(N_of_AssetCF);
		retrive_interest_DR.resize(N_of_AssetCF);
		periodEnd_notional_DR.resize(N_of_AssetCF);
		periodEnd_cashflow_DR.resize(N_of_AssetCF);
		DR_amount.resize(N_of_AssetCF);

		retrive_notional_DR[0] = 0.0;
		retrive_interest_DR[0] = 0.0;
		periodEnd_notional_DR[0] = original_AssetCF[0][3];
		periodEnd_cashflow_DR[0] = 0.0;
		DR_amount[0] = 0.0;

		//存储证券端的相关数据
		dates_TrancheCF.resize(N_of_AssetCF);
		tax_amount.resize(N_of_AssetCF); tax_amount[0] = 0.0;
		
		int N = N_of_Senior + N_of_Equity;
		retrive_interest_TrancheCF.resize(N);
		retrive_notional_TrancheCF.resize(N);
		periodEnd_notional_TrancheCF.resize(N);
		periodEnd_cashflow_TrancheCF.resize(N);
		dfs.resize(N);
		for (int j = 0; j < N; ++j)
		{
			retrive_interest_TrancheCF[j].resize(N_of_AssetCF);
			retrive_notional_TrancheCF[j].resize(N_of_AssetCF);
			periodEnd_notional_TrancheCF[j].resize(N_of_AssetCF);
			periodEnd_cashflow_TrancheCF[j].resize(N_of_AssetCF);

			periodEnd_notional_TrancheCF[j][0] = tranche_notional[j];//存储估值日，各个tranche的未偿还期末本金余额
			retrive_interest_TrancheCF[j][0] = 0.0;
			retrive_notional_TrancheCF[j][0] = 0.0;
			periodEnd_cashflow_TrancheCF[j][0] = 0.0;
		}



	}
	else
		throw"Error in Original Asset Cash Flow Data, please check!";

}
void CLO::update_AssetCF()
{
	//输入数据：
	//1. 0早偿0违约时, 资产端现金流，(数据来源于: 发行公告及每期信托报告)
	//2. 早偿及违约参数

	//输出数据:
	//存在早偿和违约参数时的资产端现金流
	if (original_AssetCF.size() == 0 || original_AssetCF[0].size() == 0)throw"Please set the original asset cash flow first!";
	if (CPR == 0 && DR == 0)
	{
		updated_AssetCF = original_AssetCF;
		return;
	}
	//if (valuationDate.getExcelDay() < lastDate || valuationDate.getExcelDay() > nextDate|| N_of_AssetCF == 0)throw"The original Asset Data is out-of-date!";

	std::vector<double> projected_retrive_notional(N_of_AssetCF);//考虑早偿因素后的,计划收回本金
	std::vector<double> projected_retrive_interest(N_of_AssetCF);//考虑早偿因素后的,计划收回利息

	if (CPR >= 0)//可以处理存在早偿和不存在早偿两种情形
	{

		//处理早偿率
		double cum_retrive_notional = 0.0; //0早偿时累计的收回本金； 用于计算早偿金额
		projected_retrive_notional[0] = 0.0;
		projected_retrive_interest[0] = 0.0;
		double SMM = 0.0;
		double days = 0.0;

		for (int i = 1; i < N_of_AssetCF; ++i)
		{
			/*更新每一期的SMM,因为在优先级结束前后可能不一致*/
			days = dates_AssetCF[i] - dates_AssetCF[i - 1];
			//1 + CPR = (1 + SMM) ^ (365 / days)
			SMM = 1 - pow(1 - CPR, days / 365.0);
			cum_retrive_notional = cum_retrive_notional + original_AssetCF[i][2];//截止i期累计收回本金
			projected_retrive_notional[i] = original_AssetCF[i][2] * pow(1-SMM, i - 1);
			projected_retrive_interest[i] = original_AssetCF[i][1];//wind目前早偿因素对interest没有影响
			CPR_amount[i] = (notional - cum_retrive_notional) * pow(1 - SMM, i - 1) * SMM;

			retrive_interest_CPR[i] = original_AssetCF[i][1];//wind目前早偿因素对interest没有影响
			retrive_notional_CPR[i] = projected_retrive_notional[i] + CPR_amount[i];//当期实际收回本金 = 计划收回本金+当期早偿金额
			periodEnd_notional_CPR[i] = periodEnd_notional_CPR[i - 1] - retrive_notional_CPR[i];//上期期末本金余额 - 当期实际收回本金
			periodEnd_cashflow_CPR[i] = retrive_interest_CPR[i] + retrive_notional_CPR[i];//每期现金流 = 每期实际收回利息 + 每期实际收回本金
		}
	}

	double Prob_Current_Default = 0.0;
	double Prob_Future_Default = 0.0;
	if (DR >= 0)
	{

		for (int i = 1; i < N_of_AssetCF; ++i)
		{
			projected_retrive_notional[i] = retrive_notional_CPR[i] * periodEnd_notional_DR[i - 1] / periodEnd_notional_CPR[i - 1];//存在违约时的预计回收本金
			periodEnd_notional_DR[i] = periodEnd_notional_CPR[i] * periodEnd_notional_DR[i - 1] / periodEnd_notional_CPR[i - 1];//存在违约时的预计期末余额
			DR_amount[i] = periodEnd_notional_DR[i - 1] * DR * (dates_AssetCF[i] - dates_AssetCF[i - 1]) / 365.0 * LGD;//基于上期期末余额, 计算违约金额

			//计算两个部分的违约概率
			Prob_Future_Default = DR_amount[i] / (projected_retrive_notional[i] * Default_Ratio + periodEnd_notional_DR[i]);
			Prob_Current_Default = Default_Ratio * Prob_Future_Default;

			retrive_notional_DR[i] = projected_retrive_notional[i] * (1 - Prob_Current_Default);
			periodEnd_notional_DR[i] = periodEnd_notional_DR[i] * (1 - Prob_Future_Default);
			retrive_interest_DR[i] = projected_retrive_interest[i] * (retrive_notional_DR[i] + periodEnd_notional_DR[i]) / periodEnd_notional_DR[i - 1];//预期收回利息*(当期收回本金+当期期末余额)/上期期末余额
			periodEnd_cashflow_DR[i] = retrive_interest_DR[i] + retrive_notional_DR[i];
		}
	}




}
void CLO::update_TrancheCF()
{
	//按照公告中的偿付顺序，依序偿付各级证券端的利息+本金；
	//注意资产端与证券端的日期序列不一致, 需要后期更正

	/*
		偿付流程方式一(1级优先级+1级次级):
			1. 支付税费
			2. 支付优先级利息
			3. 支付优先级本金
			4.【优先级本金偿还已结束】 支付次级本金
			5.【次级本金偿还已结束】 支付次级收益(需扣除奖励，若有)

		偿付流程方式二(1级优先级+1级次级):
			1. 支付税费
			2. 支付优先级利息
			3.【优先级本金偿还未结束】支付次级利息 //区别于方式一的点
			4. 支付优先级本金
			5.【优先级本金偿还已结束】 支付次级本金
			6.【次级本金偿还已结束】 支付次级收益(需扣除奖励，若有)

		偿付流程方式二(2级优先级+1级次级):
			1. 支付税费

		偿付流程方式二(3级优先级+1级次级):
			1. 支付税费

	*/

	//获取证券端现金流日期序列
	generate_dates_TrancheCF();

	int N = N_of_Senior + N_of_Equity;
	double days = 0.0;

	for (int i = 1; i < periodEnd_cashflow_DR.size(); ++i)
	{
		days = dates_TrancheCF[i] - dates_TrancheCF[i - 1];
		double temp = 0.0;

		//step 1: 每期税费偿付 = 资产端现金流 * 年化税费比例 * 当期days / 365.0
		tax_amount[i] = periodEnd_cashflow_DR[i] * tax_ratio * days / 365.0;
		temp = periodEnd_cashflow_DR[i] - tax_amount[i];//扣除税费后可以用于分配的金额

		//step 2: 支付各级(优先级+次级)利息
		for (int j = 0; j < N; ++j)
		{

			if (j < N - 1)
			{
				//1.是否支付优先级证券利息?
				if (periodEnd_notional_TrancheCF[j][i - 1] > 0)//当前剩余本金>0,需偿付利息
				{
					retrive_interest_TrancheCF[j][i] = periodEnd_notional_TrancheCF[j][i - 1] * coupon[j] * days / 365.0; //当期tranche利息 = 上期tranche期末本金 * coupon * days / 365.0;
				}
				else//剩余本金=0，无需偿付利息
				{
					retrive_interest_TrancheCF[j][i] = 0.0;
				}
			}
			else
			{
				//2.是否支付次级证券利息?
				if (periodEnd_notional_TrancheCF[j - 1][i - 1] > 0)//优先级剩余本金>0并且次级票息>0,则需偿付次级利息
				{
					retrive_interest_TrancheCF[j][i] = periodEnd_notional_TrancheCF[j][i - 1] * coupon[j] * days / 365.0; //当期tranche利息 = 上期tranche期末本金 * coupon * days / 365.0;
				}
				else//优先级本金已全部偿付完毕,则无需偿付次级利息
				{
					retrive_interest_TrancheCF[j][i] = 0.0;
				}
			}

			temp = temp - retrive_interest_TrancheCF[j][i];
		}

		if (temp < 0)throw"Default happened!";//不能够支付各级tranche利息, 则违约； 无法定价;

		// step 3. 支付各级本金
		for (int j = 0; j < N; ++j)
		{

			//1. 剩余本金不足以支付当前tranche的本金，则全部用于偿还当前tranche
			if (temp < periodEnd_notional_TrancheCF[j][i - 1])
			{
				retrive_notional_TrancheCF[j][i] = temp;
				periodEnd_notional_TrancheCF[j][i] = periodEnd_notional_TrancheCF[j][i - 1] - temp;
				temp = 0.0;
				for (int k = j + 1; k < N; ++k)
				{
					retrive_notional_TrancheCF[k][i] = 0.0;
					periodEnd_notional_TrancheCF[k][i] = periodEnd_notional_TrancheCF[k][i - 1];
				}
				break;
			}
			//2. 剩余本金足以支付当前tranche的本金，则偿还当前tranche所有本金，当前tranche结束
			else
			{

				retrive_notional_TrancheCF[j][i] = periodEnd_notional_TrancheCF[j][i - 1];
				periodEnd_notional_TrancheCF[j][i] = 0.0;
				temp = temp - retrive_notional_TrancheCF[j][i];
			}

			//3. 对于次级证券，本金偿付完，需考虑收益部分现金流: 收益部分需扣除award；次级收益保存在次级的interest变量中
			if (j == N - 1 && periodEnd_notional_TrancheCF[j][i] == 0.0)
			{
				retrive_interest_TrancheCF[j][i] = retrive_interest_TrancheCF[j][i] + temp * (1 - award_ratio);
			}
			
		}


		// step 4. 计算现金流 = 收回利息 + 收回本金
		for (int j = 0; j < N; ++j)
		{
			periodEnd_cashflow_TrancheCF[j][i] = retrive_notional_TrancheCF[j][i] + retrive_interest_TrancheCF[j][i];
		}
	}

}
void CLO::generate_dates_TrancheCF()
{
	if (N_of_AssetCF == 0) throw"Please set the Original Asset CF firstly!";
	if(dates_TrancheCF.size() != N_of_AssetCF)dates_TrancheCF.resize(N_of_AssetCF);
	dates_TrancheCF[0] = last_coupon_date;
	dates_TrancheCF[1] = next_coupon_date;
	dfs.resize(N_of_AssetCF); 

	int step = 0;
	char unit = 'm';

	if (coupon_frequency == CLO_Coupon_Frequency::annually) {
		step = 1;
		unit = 'y';
	}
	else if (coupon_frequency == CLO_Coupon_Frequency::semiannually) {
		step = 6;
		unit = 'm';
	}
	else if (coupon_frequency == CLO_Coupon_Frequency::quarterly) {
		step = 1;
		unit = 'q';
	}
	else if (coupon_frequency == CLO_Coupon_Frequency::monthly) {
		step = 1;
		unit = 'm';
	}
	//当是一些特殊情况时
	else{
		step= 1,
		unit = 't';
	}


	for (int i = 2; i < N_of_AssetCF; ++i)
	{
		dates_TrancheCF[i] = next_coupon_date.AddPeriod(step * (i - 1), unit, false);
	}

}
void CLO::set_yld(double _yld)
{
	if (_yld <= 0)throw"Error value of yield to maturity!";
	if (dfs.size() != N_of_AssetCF || N_of_AssetCF == 0)throw"Please set the original asset cash flow firstly!";
	if (yld == _yld && dfs[N_of_AssetCF-1] <= 1.0)return;//无须更新贴现因子
	yld = _yld;

	//计算每一期上的到期收益率
	double period_yld = yld;
	if (coupon_frequency == CLO_Coupon_Frequency::annually);
	else if (coupon_frequency == CLO_Coupon_Frequency::semiannually) period_yld = yld / 2.0;
	else if (coupon_frequency == CLO_Coupon_Frequency::quarterly) period_yld = yld / 4.0;
	else if (coupon_frequency == CLO_Coupon_Frequency::monthly) period_yld = yld / 12.0;
	else if (coupon_frequency == CLO_Coupon_Frequency::paygap) period_yld = yld/ 24;
	//这里的paygap在额外的特殊情况下应进行重新赋值，偶有交付频率为10天，20天的情况

	for (int i = 0; i < N_of_AssetCF; ++i)
	{
		//1. 估值日前的贴现因子=1.0
		if (dates_TrancheCF[i] <= valuationDate)dfs[i] = 1.0;
		else
		{
			//2. 估值日后的第一个日期
			if (dfs[i - 1] == 1.0) dfs[i] = 1.0 / pow(1 + period_yld, (dates_TrancheCF[i] - valuationDate) / (dates_TrancheCF[i] - dates_TrancheCF[i-1]));
			//3. 估值日后的其他日期
			else dfs[i] = dfs[i-1]/ (1 + period_yld);
		}
	}
	



}
void CLO::calculate()
{
	//计算各个tranche的价格
	if (yld <= 0) throw"Please set the yield to maturity first!";
	int N = N_of_Equity + N_of_Senior;
	dirty_price.resize(N);
	clean_price.resize(N);
	accrued_interest.resize(N);

	
	for (int i = 0; i < N; ++i)
	{
		if (tranche_notional[i] <= 0.0)
		{
			dirty_price[i] = 0.0;
			clean_price[i] = 0.0;
			accrued_interest[i] = 0.0;
			continue;
		}

		//1. 计算全价
		double sum = 0.0;
		for (int j = 1; j < N_of_AssetCF; ++j)
		{
			sum += dfs[j] * periodEnd_cashflow_TrancheCF[i][j];//贴现因子*现金流
		}
		dirty_price[i] = 100 * sum / tranche_notional[i];

		//2. 计算应计利息

		//优先级应计利息
		if (i < N - 1) accrued_interest[i] = 100.0 * coupon[i] * (valuationDate.getExcelDay() - last_coupon_date.getExcelDay()) / 365.0;
		//次级应计利息, 优先级偿付完毕前可能有应计利息？
		//if (i == N - 1)accrued_interest[i] = 100.0 * (tranche_notional[i - 1] > 0 ? coupon[i] : 0.0) * (valuationDate.getExcelDay() - last_coupon_date.getExcelDay()) / 365.0;
		if (i == N - 1)accrued_interest[i] = 0.0;

		//3. 计算净价
		clean_price[i] = dirty_price[i] - accrued_interest[i];

		cout << "PolyU Method : tranche-" << i + 1 << ": dirty price=" << dirty_price[i] << "; accrued interest=" << accrued_interest[i] << "; clean price=" << clean_price[i] << endl;

	}

}
void CLO::calculate_wind(int _tranche_index, string _trancheCF_csvName, std::vector<double> _results)
{

	//计算各个tranche的价格
	if (yld <= 0) throw"Please set the yield to maturity first!";
	_results.resize(3);

	//=============从csv文件中获取wind证券端现金流用于定价===============
	wind_trancheCF.clear();
	wind_trancheCF.resize(dfs.size());
	for (auto& each : wind_trancheCF)each = 0.0;

	ifstream infile(_trancheCF_csvName.c_str(), ios::in);
	if (!infile.is_open())
	{
		cout << "Error: opening file failed" << endl;
		exit(1);
	}
	string line;
	istringstream sin;
	int i = 0;
	while (getline(infile, line))
	{
		std::vector<double> temp;
		sin.clear();
		sin.str(line);
		string s0;
		while (getline(sin, s0, ','))
		{
			temp.push_back(stod(s0)); //cout << stod(s0) << ",";
		}
		wind_trancheCF[i++] = (temp[1] + temp[2]);//证券端本金+证券端利息=证券端现金流
	}
	infile.close();


	//1. 计算全价
	double sum = 0.0;
	for (int j = 1; j < dfs.size(); ++j)
	{
		sum += dfs[j] * wind_trancheCF[j-1];//贴现因子*现金流
	}
	double dirty_price_wind = 100 * sum / tranche_notional[_tranche_index-1];

	//2. 计算应计利息
	double accrued_interest_wind = accrued_interest[_tranche_index - 1];

	//3. 计算净价
	double clean_price_wind = dirty_price_wind - accrued_interest_wind;

	_results[0] = dirty_price_wind;
	_results[1] = accrued_interest_wind;
	_results[2] = clean_price_wind;
	cout << "Wind Method : tranche-" << _tranche_index << ": dirty price=" << dirty_price_wind << "; accrued interest=" << accrued_interest_wind << "; clean price=" << clean_price_wind << endl;

}
void CLO::calculate_wind(int _tranche_index, std::vector<std::vector<double>> _trancheCF_vector, std::vector<double> _results)
{

	//计算各个tranche的价格
	if (yld <= 0) throw"Please set the yield to maturity first!";
	_results.resize(3);

	//=============从csv文件中获取wind证券端现金流用于定价===============
	wind_trancheCF.clear();
	wind_trancheCF.resize(dfs.size());
	for (auto& each : wind_trancheCF)each = 0.0;

	for (int i = 0; i < _trancheCF_vector.size(); ++i) wind_trancheCF[i] = (_trancheCF_vector[i][1] + _trancheCF_vector[i][2]);//证券端本金+证券端利息=证券端现金流


	//1. 计算全价
	double sum = 0.0;
	for (int j = 1; j < dfs.size(); ++j)
	{
		sum += dfs[j] * wind_trancheCF[j - 1];//贴现因子*现金流
	}
	double dirty_price_wind = 100 * sum / tranche_notional[_tranche_index - 1];

	//2. 计算应计利息
	double accrued_interest_wind = accrued_interest[_tranche_index - 1];

	//3. 计算净价
	double clean_price_wind = dirty_price_wind - accrued_interest_wind;

	_results[0] = dirty_price_wind;
	_results[1] = accrued_interest_wind;
	_results[2] = clean_price_wind;
	cout << "Wind Method : tranche-" << _tranche_index << ": dirty price=" << dirty_price_wind << "; accrued interest=" << accrued_interest_wind << "; clean price=" << clean_price_wind << endl;

}
void CLO::get_price(std::vector<double>& _dirty_price, std::vector<double>& _clean_price, std::vector<double>& _accrued_interest)
{

	if (dirty_price.size() != N_of_Equity + N_of_Senior || clean_price.size() != N_of_Equity + N_of_Senior || accrued_interest.size() != N_of_Equity + N_of_Senior
		|| N_of_Equity + N_of_Senior == 0)throw"Please perform the calculation first\n";

	_dirty_price = dirty_price;
	_clean_price = clean_price;
	_accrued_interest = accrued_interest;

}
int main()
{
	size_t N_of_Senior = 1;
	size_t N_of_Equity = 1;
	std::vector<double> coupon = { 0.048,0.02 };
	std::vector<double> tranche_notional = { 147730100,480864245.4};
	double CPR = 0.2;
	double DR = 0.05;
	double LGD = 1.0;
	double Default_Ratio = 2.0;
	double yld = 0.05;
	double award_ratio = 0.0;
	double tax_ratio = 0.0045 * 12;
	QDate valuation_date = QDate("2023-09-12");
	QDate last_coupon_date = QDate("2023-08-26");
	QDate next_coupon_date = QDate("2023-09-26");
	CLO_Coupon_Frequency coupon_frequency = CLO_Coupon_Frequency::monthly;
	string csv_file_name = "originalAsset_1789048.csv";
	auto clo(std::make_unique<CLO>(N_of_Senior, N_of_Equity, valuation_date, coupon, tranche_notional,
		last_coupon_date, next_coupon_date, coupon_frequency,
		tax_ratio, award_ratio,
		csv_file_name));

	//使用PolyU计算的证券端数据计算价格
	clo->set_AssetCF_paras(CPR, DR, LGD, Default_Ratio);
	clo->();
	clo->update_TrancheCF();
	clo->set_yld(yld);
	clo->calculate();

	//使用wind证券端数据直接贴现计算wind的贴现价格；
	std::vector<double> wind_results;
	string tranche1_csvname = "windTranche_1789048_CPR20_DR5.csv";
	clo->calculate_wind(1,tranche1_csvname, wind_results);
	string tranche2_csvname = "windTranche_1789049_CPR20_DR5.csv";
	clo->calculate_wind(2, tranche2_csvname, wind_results);
	return 0;

}