#include <iostream>
#include <fstream>//
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <vector>
#include "date.h"

using namespace std;
using namespace boost::numeric::ublas;//ʹ��boost�е�matrix

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
//���������Щ���������Ʃ���ټ���15��ȣ�����ʹ��paygap=24;���ֵ��ÿ��Ӧ�ø�����������������¸�ֵ
	monthly = 12,//һ��֧���Ĵ���
	quarterly = 4,
	semiannually = 2,
	annually = 1,
	paygap =24,
};

class CLO
{
public:
	/*
		���캯���д洢�����ʲ��˵��������:
		1. ���ȼ��ʹμ�����tranche�ĸ���
		2. ����tranche��coupon���У� ��Ϊ����ĳ��trache���ۣ�ͨ����������tranche��coupons,������Ϊ���캯���������ݽ���
		3. ��ֵ����
		4. 0�糥0ΥԼ���ʲ�����������
	*/

	//obtain the asset cash flow from csv file;
	CLO(
		//��������
		size_t _N_of_Senior, //���ȼ�����
		size_t _N_of_Equity, //�μ�����
		QDate _valuationDate,//��ֵ����

		//֤ȯ����ز���
		std::vector<double> _coupon, //��tranche��coupon Ʊ������
		std::vector<double> _tranche_notional, //��tranche����ĩ����
		QDate _last_coupon_date, //��tranche��һ����Ϣ����
		QDate _next_coupon_date, //��tranche��һ����Ϣ����
		CLO_Coupon_Frequency _coupon_frequency,//��tranche��coupon֧��Ƶ��

		//Ӱ��֤ȯ�˷���Ĳ���
		double _tax_ratio,//˰�ѱ���
		//bool _pay_couponToEquityTranche_beforeEndofSeniorTranche, //���ȼ�����ǰ�Ƿ�֧���μ���Ϣ
		double _award_ratio,//�μ�������֧���Ľ�������
		

		//ԭʼ�ʲ�������
		string _infile_csvName);

	//obtain the asset cash flow from vector of vector
	CLO(
		//��������
		size_t _N_of_Senior, 
		size_t _N_of_Equity, 
		QDate _valuationDate,

		//֤ȯ����ز���
		std::vector<double> _coupon,  //��tranche��coupon
		std::vector<double> _tranche_notional, //��tranche����ĩ����
		QDate _last_coupon_date, //��tranche��һ����Ϣ����
		QDate _next_coupon_date, //��tranche��һ����Ϣ����
		CLO_Coupon_Frequency _coupon_frequency,//��tranche��coupon֧��Ƶ��

		//Ӱ��֤ȯ�˷���Ĳ���
		double _tax_ratio,//˰�ѱ���
		//bool _pay_couponToEquityTranche_beforeEndofSeniorTranche, //���ȼ�����ǰ�Ƿ�֧���μ���Ϣ
		double _award_ratio,//�μ�������֧���Ľ�������

		//ԭʼ�ʲ�������
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
	void update_AssetCF();//�������º���ʲ�������
	void update_TrancheCF();//�������º��֤ȯ������

	void generate_dates_TrancheCF();
	void set_yld(double _yld);//���ݵ��������ʼ��������������
	void calculate();//�����ʲ����ֽ�������������; ���㾻�ۣ�ȫ�ۣ�Ӧ����Ϣ�����ݣ�
	void calculate_wind(int _tranche_index, string _trancheCF_csvName, std::vector<double> _results);//����wind������֤ȯ������ֱ�����֣�����۸�; tranche_index��1��ʼ
	void calculate_wind(int _tranche_index, std::vector<std::vector<double>> _trancheCF_vector, std::vector<double> _results);//����wind������֤ȯ������ֱ�����֣�����۸�;tranche_index��1��ʼ
	void get_price(std::vector<double>& _dirty_price, std::vector<double>& _clean_price, std::vector<double>& _accrued_interest);//��ȡ��ֵ��Ϣ


private:

	/*�ʲ��ع��е�����*/
	double notional;//�ʲ�����ĩ�������
	size_t N_of_Senior;//����֤ȯ����
	size_t N_of_Equity;//�μ�֤ȯ����
	//frequency poolAsset_frequency;//�ʲ����ʲ���ϢƵ�ʣ����ܲ�����ʼ�ղ��䣻 ��22����9���ȼ�����ǰΪ����һ�Σ����ȼ�����֮��Ϊ3��һ�Σ�
	std::vector<double> coupon;//size�������N_of_Senior+N_of_Equity; ֤ȯ��ƱϢ��
	std::vector<double> tranche_notional; //��tranche����ĩ����
	std::vector<double>  ; //��ֹ��ֵ��,��tranche���ۼ�Ӧ����Ϣ
	QDate valuationDate;//��ֵ����
	QDate lastDate; //��һ���ʲ����ֽ�����������
	QDate nextDate; //��һ���ʲ����ֽ�����������
	QDate last_coupon_date;//��һ��tranche��Ϣ��
	QDate next_coupon_date;//��һ��tranche��Ϣ��
	CLO_Coupon_Frequency coupon_frequency;//tranche�˸�ϢƵ��
	//bool pay_couponToEquityTranche_beforeEndofSeniorTranche; //���ȼ�����ǰ�Ƿ�֧���μ���Ϣ


	/*�����ʲ����ֽ�������ز���*/
	double CPR;//�껯�糥�� 
	//double SMM;//ÿһ�ڵ��糥��
	/*SMM��CPR�Ĺ�ϵ:
		һ���12�ڣ�1 + CPR = (1 + SMM)^12
		һ���4�ڣ� 1 + CPR = (1 + SMM)^4
		һ�����Σ�  1 + CPR = (1 + SMM)^(365/days)
	*/
	double DR; //�껯ΥԼ��
	double LGD;//ΥԼ��ʧ��
	double Default_Ratio;//�����ջز���ΥԼ����/δ���ջز���ΥԼ����
	size_t N_of_AssetCF;//�ʲ����ֽ�������
	double yld;//�����õĵ���������

	/*ȷ��֤ȯ������*/
	CLO_Tranche tranche;//��ǰ֤ȯ����
	/*Ӱ��֤ȯ�˷���Ĳ��ֲ���*/
	double tax_ratio;//����˰�ѷ��ñ���; �껯˰�ѱ���
	double award_ratio;//�μ�֤ȯ����֮��, �ʲ����ֽ��������Ͼ���Ϊ�μ�֤ȯ�����淵�ظ��μ�֤ȯ�����ߣ���������һ��award�ȸ��������

	/*�ʲ��������������*/
	std::vector<int> dates_AssetCF;//�ʲ����ֽ�����������
	std::vector<std::vector<double>> original_AssetCF;//0�糥0ΥԼ�ʲ����ֽ���
	std::vector<std::vector<double>> updated_AssetCF;//�����糥�ʺ�ΥԼ�ʸ��º���ʲ����ֽ���
	/*�����糥���غ�õ����������*/
	std::vector<double> retrive_notional_CPR;//�����糥���غ��,ʵ���ջر���
	std::vector<double> retrive_interest_CPR;//�����糥���غ��,ʵ���ջ���Ϣ(windĿǰ�糥���ض�interestû��Ӱ��)
	std::vector<double> periodEnd_notional_CPR;//�����糥���ص�ÿ����ĩ�������
	std::vector<double> periodEnd_cashflow_CPR;//�����糥���ص�ÿ����ĩ�ʲ����ֽ����������ջ���Ϣ+�ջر���
	std::vector<double> CPR_amount;//ÿ���糥���
	/*����ΥԼ���غ�õ����������*/
	std::vector<double> retrive_notional_DR;//����ΥԼ���غ��,ʵ���ջر���
	std::vector<double> retrive_interest_DR;//����ΥԼ���غ��,ʵ���ջ���Ϣ
	std::vector<double> periodEnd_notional_DR;//����ΥԼ���ص�ÿ����ĩ�������
	std::vector<double> periodEnd_cashflow_DR;//����ΥԼ���ص�ÿ����ĩ�ʲ����ֽ����������ջ���Ϣ+�ջر���
	std::vector<double> DR_amount;//ÿ��ΥԼ���

	/*֤ȯ�������������*/
	std::vector<int> dates_TrancheCF;//֤ȯ���ֽ�����������, ���������г���Ĭ�ϵ����ʲ��˳���; ͨ�������õ���ô��������
	std::vector<double> tax_amount;//ÿ��˰�ѿ۳�
	std::vector<double> dfs;//��֤ȯ�����鳤��һ�µģ�������������
	std::vector<std::vector<double>> retrive_interest_TrancheCF;//���size() == tranche����
	std::vector<std::vector<double>> retrive_notional_TrancheCF;//���size() == tranche����
	std::vector<std::vector<double>> periodEnd_notional_TrancheCF;//���size() == tranche����
	std::vector<std::vector<double>> periodEnd_cashflow_TrancheCF;//���size() == tranche����

	/*��Դ��wind��֤ȯ������*/
	std::vector<double> wind_trancheCF;//��Դ��wind��֤ȯ�����ݣ�����ֱ�Ӹ���wind�ֽ�������wind�ļ۸�; cash flow = notional + interest

	/*CLO�۸�*/
	std::vector<double> dirty_price;//size() == tranche����
	std::vector<double> clean_price;//size() == tranche����
	std::vector<double> accrued_interest;//size() == tranche����
	
};

CLO::CLO(		//��������
	size_t _N_of_Senior, //���ȼ�����
	size_t _N_of_Equity, //�μ�����
	QDate _valuationDate,//��ֵ����
	//֤ȯ����ز���
	std::vector<double> _coupon, //��tranche��coupon
	std::vector<double> _tranche_notional, //��tranche����ĩ����
	QDate _last_coupon_date, //��tranche��һ����Ϣ����
	QDate _next_coupon_date, //��tranche��һ����Ϣ����
	CLO_Coupon_Frequency _coupon_frequency,//��tranche��coupon֧��Ƶ��
	//Ӱ��֤ȯ�˷���Ĳ���
	double _tax_ratio,//˰�ѱ���
	//bool _pay_couponToEquityTranche_beforeEndofSeniorTranche, //���ȼ�����ǰ�Ƿ�֧���μ���Ϣ
	double _award_ratio,//�μ�������֧���Ľ�������
	//ԭʼ�ʲ�������
	string _infile_csvName):
	N_of_Senior(_N_of_Senior), N_of_Equity(_N_of_Equity), valuationDate(_valuationDate),
	coupon(_coupon), tranche_notional(_tranche_notional),
	last_coupon_date(_last_coupon_date),next_coupon_date(_next_coupon_date), coupon_frequency(_coupon_frequency),
	tax_ratio(_tax_ratio), award_ratio(_award_ratio)
{
	if (_N_of_Senior <= 0 || _N_of_Senior >3 || _N_of_Equity != 1)throw"Cannot deal with CLO of this structure!";
	if (_coupon.size() != _N_of_Senior + _N_of_Equity)throw"Size of Coupons must equal to number of tranches!";

	//=============��csv�ļ��л�ȡ0�糥0ΥԼ�ʲ����ֽ������ڶ���===============
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
	//=============��csv�ļ��л�ȡ0�糥0ΥԼ�ʲ����ֽ������ڶ���===============

	//���²�����set_AssetCF_paras�����л��
	CPR = 0.0;
	DR = 0.0;
	LGD = 0.0;
	Default_Ratio = 0;

	//���²�����set_tranche�����л��
	tranche = CLO_Tranche::NotSet;

}

CLO::CLO(		//��������
	size_t _N_of_Senior,
	size_t _N_of_Equity,
	QDate _valuationDate,

	//֤ȯ����ز���
	std::vector<double> _coupon,
	std::vector<double> _tranche_notional, //��tranche����ĩ����
	QDate _last_coupon_date, //��tranche��һ����Ϣ����
	QDate _next_coupon_date, //��tranche��һ����Ϣ����
	CLO_Coupon_Frequency _coupon_frequency,//��tranche��coupon֧��Ƶ��
	//Ӱ��֤ȯ�˷���Ĳ���
	double _tax_ratio,//˰�ѱ���
	//bool _pay_couponToEquityTranche_beforeEndofSeniorTranche, //���ȼ�����ǰ�Ƿ�֧���μ���Ϣ
	double _award_ratio,//�μ�������֧���Ľ�������
	//ԭʼ�ʲ�������
	std::vector<std::vector<double>> _original_AssetCF) :
	N_of_Senior(_N_of_Senior), N_of_Equity(_N_of_Equity), valuationDate(_valuationDate),
	coupon(_coupon), tranche_notional(_tranche_notional),
	last_coupon_date(_last_coupon_date), next_coupon_date(_next_coupon_date), coupon_frequency(_coupon_frequency),
	tax_ratio(_tax_ratio), award_ratio(_award_ratio),
	original_AssetCF(_original_AssetCF),updated_AssetCF(_original_AssetCF)
{
	if (_N_of_Senior <= 0 || _N_of_Senior > 3 || _N_of_Equity != 1)throw"Cannot deal with CLO of this structure!";
	if (_coupon.size() != _N_of_Senior + _N_of_Equity)throw"Size of Coupons must equal to number of tranches!";

	//=============��vector�����л�ȡ0�糥0ΥԼ�ʲ����ֽ������ڶ���===============
	set_Original_AssetCF();
	//=============��vector�����л�ȡ0�糥0ΥԼ�ʲ����ֽ������ڶ���===============
	
	//���²�����set_AssetCF_paras�����л��
	CPR = 0.0;
	DR = 0.0;
	LGD = 0.0;
	Default_Ratio = 0;

	//���²�����set_tranche�����л��
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
		for (int i = 0; i < N_of_AssetCF; ++i)dates_AssetCF[i] = original_AssetCF[i][0];//�洢��������

		//�洢�糥Ӱ�����ʲ�������
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

		//�洢ΥԼӰ�����ʲ�������
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

		//�洢֤ȯ�˵��������
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

			periodEnd_notional_TrancheCF[j][0] = tranche_notional[j];//�洢��ֵ�գ�����tranche��δ������ĩ�������
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
	//�������ݣ�
	//1. 0�糥0ΥԼʱ, �ʲ����ֽ�����(������Դ��: ���й��漰ÿ�����б���)
	//2. �糥��ΥԼ����

	//�������:
	//�����糥��ΥԼ����ʱ���ʲ����ֽ���
	if (original_AssetCF.size() == 0 || original_AssetCF[0].size() == 0)throw"Please set the original asset cash flow first!";
	if (CPR == 0 && DR == 0)
	{
		updated_AssetCF = original_AssetCF;
		return;
	}
	//if (valuationDate.getExcelDay() < lastDate || valuationDate.getExcelDay() > nextDate|| N_of_AssetCF == 0)throw"The original Asset Data is out-of-date!";

	std::vector<double> projected_retrive_notional(N_of_AssetCF);//�����糥���غ��,�ƻ��ջر���
	std::vector<double> projected_retrive_interest(N_of_AssetCF);//�����糥���غ��,�ƻ��ջ���Ϣ

	if (CPR >= 0)//���Դ�������糥�Ͳ������糥��������
	{

		//�����糥��
		double cum_retrive_notional = 0.0; //0�糥ʱ�ۼƵ��ջر��� ���ڼ����糥���
		projected_retrive_notional[0] = 0.0;
		projected_retrive_interest[0] = 0.0;
		double SMM = 0.0;
		double days = 0.0;

		for (int i = 1; i < N_of_AssetCF; ++i)
		{
			/*����ÿһ�ڵ�SMM,��Ϊ�����ȼ�����ǰ����ܲ�һ��*/
			days = dates_AssetCF[i] - dates_AssetCF[i - 1];
			//1 + CPR = (1 + SMM) ^ (365 / days)
			SMM = 1 - pow(1 - CPR, days / 365.0);
			cum_retrive_notional = cum_retrive_notional + original_AssetCF[i][2];//��ֹi���ۼ��ջر���
			projected_retrive_notional[i] = original_AssetCF[i][2] * pow(1-SMM, i - 1);
			projected_retrive_interest[i] = original_AssetCF[i][1];//windĿǰ�糥���ض�interestû��Ӱ��
			CPR_amount[i] = (notional - cum_retrive_notional) * pow(1 - SMM, i - 1) * SMM;

			retrive_interest_CPR[i] = original_AssetCF[i][1];//windĿǰ�糥���ض�interestû��Ӱ��
			retrive_notional_CPR[i] = projected_retrive_notional[i] + CPR_amount[i];//����ʵ���ջر��� = �ƻ��ջر���+�����糥���
			periodEnd_notional_CPR[i] = periodEnd_notional_CPR[i - 1] - retrive_notional_CPR[i];//������ĩ������� - ����ʵ���ջر���
			periodEnd_cashflow_CPR[i] = retrive_interest_CPR[i] + retrive_notional_CPR[i];//ÿ���ֽ��� = ÿ��ʵ���ջ���Ϣ + ÿ��ʵ���ջر���
		}
	}

	double Prob_Current_Default = 0.0;
	double Prob_Future_Default = 0.0;
	if (DR >= 0)
	{

		for (int i = 1; i < N_of_AssetCF; ++i)
		{
			projected_retrive_notional[i] = retrive_notional_CPR[i] * periodEnd_notional_DR[i - 1] / periodEnd_notional_CPR[i - 1];//����ΥԼʱ��Ԥ�ƻ��ձ���
			periodEnd_notional_DR[i] = periodEnd_notional_CPR[i] * periodEnd_notional_DR[i - 1] / periodEnd_notional_CPR[i - 1];//����ΥԼʱ��Ԥ����ĩ���
			DR_amount[i] = periodEnd_notional_DR[i - 1] * DR * (dates_AssetCF[i] - dates_AssetCF[i - 1]) / 365.0 * LGD;//����������ĩ���, ����ΥԼ���

			//�����������ֵ�ΥԼ����
			Prob_Future_Default = DR_amount[i] / (projected_retrive_notional[i] * Default_Ratio + periodEnd_notional_DR[i]);
			Prob_Current_Default = Default_Ratio * Prob_Future_Default;

			retrive_notional_DR[i] = projected_retrive_notional[i] * (1 - Prob_Current_Default);
			periodEnd_notional_DR[i] = periodEnd_notional_DR[i] * (1 - Prob_Future_Default);
			retrive_interest_DR[i] = projected_retrive_interest[i] * (retrive_notional_DR[i] + periodEnd_notional_DR[i]) / periodEnd_notional_DR[i - 1];//Ԥ���ջ���Ϣ*(�����ջر���+������ĩ���)/������ĩ���
			periodEnd_cashflow_DR[i] = retrive_interest_DR[i] + retrive_notional_DR[i];
		}
	}




}
void CLO::update_TrancheCF()
{
	//���չ����еĳ���˳�����򳥸�����֤ȯ�˵���Ϣ+����
	//ע���ʲ�����֤ȯ�˵��������в�һ��, ��Ҫ���ڸ���

	/*
		�������̷�ʽһ(1�����ȼ�+1���μ�):
			1. ֧��˰��
			2. ֧�����ȼ���Ϣ
			3. ֧�����ȼ�����
			4.�����ȼ����𳥻��ѽ����� ֧���μ�����
			5.���μ����𳥻��ѽ����� ֧���μ�����(��۳�����������)

		�������̷�ʽ��(1�����ȼ�+1���μ�):
			1. ֧��˰��
			2. ֧�����ȼ���Ϣ
			3.�����ȼ����𳥻�δ������֧���μ���Ϣ //�����ڷ�ʽһ�ĵ�
			4. ֧�����ȼ�����
			5.�����ȼ����𳥻��ѽ����� ֧���μ�����
			6.���μ����𳥻��ѽ����� ֧���μ�����(��۳�����������)

		�������̷�ʽ��(2�����ȼ�+1���μ�):
			1. ֧��˰��

		�������̷�ʽ��(3�����ȼ�+1���μ�):
			1. ֧��˰��

	*/

	//��ȡ֤ȯ���ֽ�����������
	generate_dates_TrancheCF();

	int N = N_of_Senior + N_of_Equity;
	double days = 0.0;

	for (int i = 1; i < periodEnd_cashflow_DR.size(); ++i)
	{
		days = dates_TrancheCF[i] - dates_TrancheCF[i - 1];
		double temp = 0.0;

		//step 1: ÿ��˰�ѳ��� = �ʲ����ֽ��� * �껯˰�ѱ��� * ����days / 365.0
		tax_amount[i] = periodEnd_cashflow_DR[i] * tax_ratio * days / 365.0;
		temp = periodEnd_cashflow_DR[i] - tax_amount[i];//�۳�˰�Ѻ�������ڷ���Ľ��

		//step 2: ֧������(���ȼ�+�μ�)��Ϣ
		for (int j = 0; j < N; ++j)
		{

			if (j < N - 1)
			{
				//1.�Ƿ�֧�����ȼ�֤ȯ��Ϣ?
				if (periodEnd_notional_TrancheCF[j][i - 1] > 0)//��ǰʣ�౾��>0,�賥����Ϣ
				{
					retrive_interest_TrancheCF[j][i] = periodEnd_notional_TrancheCF[j][i - 1] * coupon[j] * days / 365.0; //����tranche��Ϣ = ����tranche��ĩ���� * coupon * days / 365.0;
				}
				else//ʣ�౾��=0�����賥����Ϣ
				{
					retrive_interest_TrancheCF[j][i] = 0.0;
				}
			}
			else
			{
				//2.�Ƿ�֧���μ�֤ȯ��Ϣ?
				if (periodEnd_notional_TrancheCF[j - 1][i - 1] > 0)//���ȼ�ʣ�౾��>0���Ҵμ�ƱϢ>0,���賥���μ���Ϣ
				{
					retrive_interest_TrancheCF[j][i] = periodEnd_notional_TrancheCF[j][i - 1] * coupon[j] * days / 365.0; //����tranche��Ϣ = ����tranche��ĩ���� * coupon * days / 365.0;
				}
				else//���ȼ�������ȫ���������,�����賥���μ���Ϣ
				{
					retrive_interest_TrancheCF[j][i] = 0.0;
				}
			}

			temp = temp - retrive_interest_TrancheCF[j][i];
		}

		if (temp < 0)throw"Default happened!";//���ܹ�֧������tranche��Ϣ, ��ΥԼ�� �޷�����;

		// step 3. ֧����������
		for (int j = 0; j < N; ++j)
		{

			//1. ʣ�౾������֧����ǰtranche�ı�����ȫ�����ڳ�����ǰtranche
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
			//2. ʣ�౾������֧����ǰtranche�ı����򳥻���ǰtranche���б��𣬵�ǰtranche����
			else
			{

				retrive_notional_TrancheCF[j][i] = periodEnd_notional_TrancheCF[j][i - 1];
				periodEnd_notional_TrancheCF[j][i] = 0.0;
				temp = temp - retrive_notional_TrancheCF[j][i];
			}

			//3. ���ڴμ�֤ȯ�����𳥸��꣬�迼�����沿���ֽ���: ���沿����۳�award���μ����汣���ڴμ���interest������
			if (j == N - 1 && periodEnd_notional_TrancheCF[j][i] == 0.0)
			{
				retrive_interest_TrancheCF[j][i] = retrive_interest_TrancheCF[j][i] + temp * (1 - award_ratio);
			}
			
		}


		// step 4. �����ֽ��� = �ջ���Ϣ + �ջر���
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
	//����һЩ�������ʱ
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
	if (yld == _yld && dfs[N_of_AssetCF-1] <= 1.0)return;//���������������
	yld = _yld;

	//����ÿһ���ϵĵ���������
	double period_yld = yld;
	if (coupon_frequency == CLO_Coupon_Frequency::annually);
	else if (coupon_frequency == CLO_Coupon_Frequency::semiannually) period_yld = yld / 2.0;
	else if (coupon_frequency == CLO_Coupon_Frequency::quarterly) period_yld = yld / 4.0;
	else if (coupon_frequency == CLO_Coupon_Frequency::monthly) period_yld = yld / 12.0;
	else if (coupon_frequency == CLO_Coupon_Frequency::paygap) period_yld = yld/ 24;
	//�����paygap�ڶ�������������Ӧ�������¸�ֵ��ż�н���Ƶ��Ϊ10�죬20������

	for (int i = 0; i < N_of_AssetCF; ++i)
	{
		//1. ��ֵ��ǰ����������=1.0
		if (dates_TrancheCF[i] <= valuationDate)dfs[i] = 1.0;
		else
		{
			//2. ��ֵ�պ�ĵ�һ������
			if (dfs[i - 1] == 1.0) dfs[i] = 1.0 / pow(1 + period_yld, (dates_TrancheCF[i] - valuationDate) / (dates_TrancheCF[i] - dates_TrancheCF[i-1]));
			//3. ��ֵ�պ����������
			else dfs[i] = dfs[i-1]/ (1 + period_yld);
		}
	}
	



}
void CLO::calculate()
{
	//�������tranche�ļ۸�
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

		//1. ����ȫ��
		double sum = 0.0;
		for (int j = 1; j < N_of_AssetCF; ++j)
		{
			sum += dfs[j] * periodEnd_cashflow_TrancheCF[i][j];//��������*�ֽ���
		}
		dirty_price[i] = 100 * sum / tranche_notional[i];

		//2. ����Ӧ����Ϣ

		//���ȼ�Ӧ����Ϣ
		if (i < N - 1) accrued_interest[i] = 100.0 * coupon[i] * (valuationDate.getExcelDay() - last_coupon_date.getExcelDay()) / 365.0;
		//�μ�Ӧ����Ϣ, ���ȼ��������ǰ������Ӧ����Ϣ��
		//if (i == N - 1)accrued_interest[i] = 100.0 * (tranche_notional[i - 1] > 0 ? coupon[i] : 0.0) * (valuationDate.getExcelDay() - last_coupon_date.getExcelDay()) / 365.0;
		if (i == N - 1)accrued_interest[i] = 0.0;

		//3. ���㾻��
		clean_price[i] = dirty_price[i] - accrued_interest[i];

		cout << "PolyU Method : tranche-" << i + 1 << ": dirty price=" << dirty_price[i] << "; accrued interest=" << accrued_interest[i] << "; clean price=" << clean_price[i] << endl;

	}

}
void CLO::calculate_wind(int _tranche_index, string _trancheCF_csvName, std::vector<double> _results)
{

	//�������tranche�ļ۸�
	if (yld <= 0) throw"Please set the yield to maturity first!";
	_results.resize(3);

	//=============��csv�ļ��л�ȡwind֤ȯ���ֽ������ڶ���===============
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
		wind_trancheCF[i++] = (temp[1] + temp[2]);//֤ȯ�˱���+֤ȯ����Ϣ=֤ȯ���ֽ���
	}
	infile.close();


	//1. ����ȫ��
	double sum = 0.0;
	for (int j = 1; j < dfs.size(); ++j)
	{
		sum += dfs[j] * wind_trancheCF[j-1];//��������*�ֽ���
	}
	double dirty_price_wind = 100 * sum / tranche_notional[_tranche_index-1];

	//2. ����Ӧ����Ϣ
	double accrued_interest_wind = accrued_interest[_tranche_index - 1];

	//3. ���㾻��
	double clean_price_wind = dirty_price_wind - accrued_interest_wind;

	_results[0] = dirty_price_wind;
	_results[1] = accrued_interest_wind;
	_results[2] = clean_price_wind;
	cout << "Wind Method : tranche-" << _tranche_index << ": dirty price=" << dirty_price_wind << "; accrued interest=" << accrued_interest_wind << "; clean price=" << clean_price_wind << endl;

}
void CLO::calculate_wind(int _tranche_index, std::vector<std::vector<double>> _trancheCF_vector, std::vector<double> _results)
{

	//�������tranche�ļ۸�
	if (yld <= 0) throw"Please set the yield to maturity first!";
	_results.resize(3);

	//=============��csv�ļ��л�ȡwind֤ȯ���ֽ������ڶ���===============
	wind_trancheCF.clear();
	wind_trancheCF.resize(dfs.size());
	for (auto& each : wind_trancheCF)each = 0.0;

	for (int i = 0; i < _trancheCF_vector.size(); ++i) wind_trancheCF[i] = (_trancheCF_vector[i][1] + _trancheCF_vector[i][2]);//֤ȯ�˱���+֤ȯ����Ϣ=֤ȯ���ֽ���


	//1. ����ȫ��
	double sum = 0.0;
	for (int j = 1; j < dfs.size(); ++j)
	{
		sum += dfs[j] * wind_trancheCF[j - 1];//��������*�ֽ���
	}
	double dirty_price_wind = 100 * sum / tranche_notional[_tranche_index - 1];

	//2. ����Ӧ����Ϣ
	double accrued_interest_wind = accrued_interest[_tranche_index - 1];

	//3. ���㾻��
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

	//ʹ��PolyU�����֤ȯ�����ݼ���۸�
	clo->set_AssetCF_paras(CPR, DR, LGD, Default_Ratio);
	clo->();
	clo->update_TrancheCF();
	clo->set_yld(yld);
	clo->calculate();

	//ʹ��wind֤ȯ������ֱ�����ּ���wind�����ּ۸�
	std::vector<double> wind_results;
	string tranche1_csvname = "windTranche_1789048_CPR20_DR5.csv";
	clo->calculate_wind(1,tranche1_csvname, wind_results);
	string tranche2_csvname = "windTranche_1789049_CPR20_DR5.csv";
	clo->calculate_wind(2, tranche2_csvname, wind_results);
	return 0;

}