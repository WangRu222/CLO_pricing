#pragma once

//========================================以下为原Constants.h中定义的一些变量和函数=============================
//=================================================================以下包含了Constants.h和Constants.h中的内容===========================================================
//==============================================================================
// ENUMERATIONS:
//==============================================================================
//------------------------------------------------------------------------------
// Adjusted / Unadjusted Flag (for dates)
//------------------------------------------------------------------------------
//=================================================================以下为Constants.h中的内容===========================================================

const size_t DEFAULT_CAPACITY = 64; /* Default collection class capacity */
const size_t DEFAULT_RESIZE = 64; /* Default collection class resize */
const size_t BITSPERBYTE = 8;  /* Number of bits per byte */
const size_t MY_NPOS = ~(size_t)0;


enum class EAdjUnadj
{
	e_Adjusted = 0,
	e_Unadjusted = 1
};
enum class ECallPut
{
	e_Call = 1,    // Used as multipliers - don't change
	e_Straddle = 0,
	e_Put = -1
};
enum class EBuySell
{
	e_Buy = 1,   // Used as mulitpliers - don't change
	e_Sell = -1
};
enum class ECleanDirty
{
	e_Clean = 0,
	e_Dirty = 1
};
enum class EFixedFloating
{
	e_Fixed = 0,
	e_Floating = 1
};
enum class EPayReceive
{
	e_Pay = -1,
	e_Receive = 1
};
enum class ERollConvention
{
	e_Standard = 0,
	e_QuarterlyIMM = 1,
	e_EndOfMonth = 2,
	e_FRN = 3,
	e_MonthlyIMM = 4,
	e_StartOfMonth = 5
};
enum class EAdjustConvention
{
	e_NoAdjustment = 0,
	e_ModifiedFollowing = 1,
	e_Following = 2,
	e_ModifiedPreceding = 3,
	e_Preceding = 4
};
enum class EFrequency
{
	//------------------------------------------------------------------------------
	// Frequency - enumerated value shows the number of coupons per year (enumerations
	//             are implicitly cast to integer).
	//------------------------------------------------------------------------------
	e_Daily = 365,
	e_Weekly = 52,
	e_Monthly = 12,
	e_BiMonthly = 6,
	e_Quarterly = 4,
	e_SemiAnnually = 2,
	e_Annually = 1,
	e_Continuous = 0
};
enum class EAccrualBasis
{
	e_30360 = 0,//分子：360 * (nEndYear - nStartYear)+ 30 * (nEndMonth - nStartMonth)+ (dEndDay - dStartDay);dStartDay最多为30;dEndDay可以为31，当且仅当自身为31，且dStartDay>=30。 分母：360
	e_30E360 = 1,//分子：360 * (nEndYear - nStartYear)+ 30 * (nEndMonth - nStartMonth)+ (dEndDay - dStartDay);***Day最多为30。分母：360
	e_Act360 = 2,//分子：实际天数。分母：360。
	e_Act365 = 3,//分子:实际天数。分母:365
	e_ActAct = 4,//分子：实际天数。分母:相应年份的实际天数。比如如果20180201-20210330,那么days(20190101-20180201)/2018年天数+ 1 + days(20210330- 20210101)/2019年天数
	e_Act29 = 5,//分子：实际天数。分母:包含2-29，则为366，否则为365
	e_Coupon = 6//
};
enum class ELongShort
{
	//------------------------------------------------------------------------------
	// Long / Short stub period flag.
	//------------------------------------------------------------------------------
	e_Long = 0,
	e_Short = 1
};
enum class EInterpolationMethod
{
	//------------------------------------------------------------------------------
	// Interpolation methods - these descibe the interpolation algorithm to be used
	// - not the data on which to operates i.e. independent on whether we are    
	//   interpolating, say, rates or discount factors.                          
	//------------------------------------------------------------------------------
	e_Exponential = 0,//df的Exponential插值代表zero rate的Linear插值，-log(Y)/X为线性
	e_SmoothedSpline = 1,
	e_Spline = 2,
	e_SplineRates = 3,
	e_LogLinear = 4,//log(Y)为线性
	e_BiParabolic = 5,
	e_Linear = 6,//Y为线性
	e_ContinousOverNight = 7,
	e_Parsimonious = 8,
	e_LinearStdev = 9,//即Y*Y*X为线性
	e_SplineStdev = 10
};
enum class EExtrapolationMethod
{
	//------------------------------------------------------------------------------
	// Extrpolation methods - these descibe the extrapolation algorithm to be used
	//------------------------------------------------------------------------------
	e_NoExtrapolation = 0,
	e_BoundaryValues = 1,
	e_SplineExtrapolation = 2
};
enum class ESearchResult
{
	//------------------------------------------------------------------------------
	// Search Result
	// - used on discount factors, but also could be used on other things.               
	//------------------------------------------------------------------------------
	e_Found = 0,
	e_InBounds = 1,
	e_LessThanBounds = 2,
	e_GreaterThanBounds = 3
};
enum class EDateType
{
	//------------------------------------------------------------------------------
	// Date formats
	//------------------------------------------------------------------------------
	e_YearOffset = 0,
	e_ExcelJulian = 1,
	e_AstroJulian = 2,
	e_Gregorian = 3
};
enum class ECurveType
{
	//------------------------------------------------------------------------------
	// Curve Types
	//------------------------------------------------------------------------------
	e_Par = 1,
	e_Forward = 2,
	e_Discount = 3,
	e_Zero = 4
};
enum class EDefaultCurveType
{
	//------------------------------------------------------------------------------
	// Default Curve type
	//------------------------------------------------------------------------------
	e_BondCurve = 101,
	e_FRNCurve = 102,
	e_DefaultSwapCurve = 103
};
enum class EStatus
{
	//------------------------------------------------------------------------------
	// Logging Level
	//------------------------------------------------------------------------------
	e_Success = 0,
	e_Information = 4,
	e_Warning = 8,
	e_Error = 12
};
enum class EPricingMethod
{
	//------------------------------------------------------------------------------
	// Pricing Method
	//------------------------------------------------------------------------------
	e_PM_FwdBSLogNormal = 0,
	e_PM_FwdBSNormal = 1,
	e_PM_ElasticityOriginal = 2,
	e_PM_Elasticity = 3,
	//e_PM_ElasticityAlwaysGetsYerMan =  4,
	e_PM_Default = 5,
	e_PM_BlackScholes = 6,
	e_PM_Trinomial = 7,
	e_PM_Binomial = 13,
	e_PM_BinomialTree = 8,
	e_PM_FwdBSSkewKurt = 9,
	//e_PM_FwdBSAdjustedLogNormal     =  10,    
	e_PM_Integration = 11,
	e_PM_BondOptionAsBSSwaption = 12
};

#define e_Default    EPricingMethod::e_PM_Default
#define e_Trinomial  EPricingMethod::e_PM_Trinomial
#define e_Elasticity EPricingMethod::e_PM_Elasticity

enum class ECalculationMethod
{
	e_AnalyticalExact,
	e_AnalyticalApprox,
	e_Numerical,
	e_Integration,
	e_BinomialTree,
	e_TrinomialTree
};
enum class EDistribution
{
	//------------------------------------------------------------------------------
	// Probability density functions
	//------------------------------------------------------------------------------
	e_LogNormal = 0,
	e_Normal = 1,
	e_Elastic = 2,
	e_SkewKurt = 3
};
enum class EBondSwapMethod
{
	//------------------------------------------------------------------------------
	// BondSwapMethod Method
	//------------------------------------------------------------------------------
	e_BondDiscount = 0,
	e_BondPar = 1,
	e_BondYield = 2,
	e_BondParDiscount = 3
};
enum class EVolatilityType
{
	//------------------------------------------------------------------------------
	// Volatility Type
	//------------------------------------------------------------------------------
	e_Absolute = 0,
	e_Relative = 1,
	e_CEV = 2
};

#define e_BondFutOpt_Swaption   EVolatilityType::e_Relative
#define e_BondFutOpt_BondOption EVolatilityType::e_Relative

enum class EBondOptionPriceAs
{
	e_BondOption,
	e_Swaption
};
enum class EBondOptionUsingVol
{
	e_BondPriceVol,
	e_SwaptionVol,
	e_ImpliedVol
};
enum class ESwaptionType
{
	e_SPayers,
	e_SReceivers,
	e_SStraddle
};
enum class ECashflowType
{
	//------------------------------------------------------------------------------
	// Cashflow Type
	//------------------------------------------------------------------------------
	e_Rate = 0,
	//    e_Swedish       = 2, // Not yet supported
	e_FixedCashflow = 2
};
enum class EPeriodType
{

	//------------------------------------------------------------------------------
	// Period Type
	//------------------------------------------------------------------------------
	e_FloatingRatePeriod = 0,
	e_FixedRatePeriod = 1,
	e_FixedCashflowPeriod = 2,
	e_PrincipalExchangePeriod = 3,
	e_MiscCashflowPeriod = 4
};
enum class ERateDomain
{
	e_Cash,
	e_Futures,
	e_Swap
};
enum class EOptionStyle
{
	e_European = 1,
	e_American = 2,
	e_Bermudan = 3
};
enum class ENotionalType
{
	//------------------------------------------------------------------------------
	// Amortisation Types
	//----------------------------------------------------------------------------
	e_Constant = 0,
	e_LinearByPaydown = 1,
	e_LinearByTarget = 2,
	e_Free = 5
};
enum class ECompoundingType
{
	//------------------------------------------------------------------------------
	// Compunding Types
	//------------------------------------------------------------------------------
	e_None = 0,
	e_WithSpread = 1,
	e_WithoutSpread = 2
};
enum class ESettlementCalcType
{
	//------------------------------------------------------------------------------
	// Settlement date calculation type
	//------------------------------------------------------------------------------
	e_ActualDays,
	e_BusinessDays,
	e_NextEndOfMonth
};
enum class ERootFindingMethod
{
	//------------------------------------------------------------------------------
	// Root finding method
	//------------------------------------------------------------------------------
	e_Bisection = 0,
	e_RegulaFalsi = 1,
	e_Secant = 2,
	e_Brent = 3
};
enum class EBarrierType
{
	e_Cap,
	e_Floor,
	e_Collar
};
enum class ECapType
{
	e_CCap,
	e_CFloor,
	e_CStraddle
};
enum class EBarrierMonitoring
{
	e_mContinuously = 1,
	e_mHourly = 2,
	e_mDayli = 3,
	e_mWeekly = 4,
	e_mMonthly = 5
};
enum class EInOutType
{
	e_In = 1,
	e_Out = 2,
	e_UpAndIn = 3,
	e_UpAndOut = 4,
	e_DownAndIn = 5,
	e_DownAndOut = 6
};
enum class EDefault
{
	e_NoDefault = 0,
	e_Defaulted = 1,
	e_PrvDefaulted = 2
};
enum class EDefaultFilter
{
	e_All = 0,
	e_DefaultedOnly,
	e_NonDefaulted
};





//const double q_Pi = 3.141592654;
const double q_Pi = 3.14159265358979;
const double q_XISQRTPI = 0.3989422804014330;	// = 1 / (Sqrt(2*pi)) 
const double q_RoundingError = 0.0000000001;

//------------------------------------------------------------------------------
// Cumulative Normal Distribution function coefficients:
//------------------------------------------------------------------------------

const double q_dNdfGamma = 0.2316419;
const double q_dNdfA1 = 0.319381530;
const double q_dNdfA2 = -0.356563782;
const double q_dNdfA3 = 1.781477937;
const double q_dNdfA4 = -1.821255978;
const double q_dNdfA5 = 1.330274429;
const double q_dSqrt2Pi = 2.50662827463100;


//------------------------------------------------------------------------------
// Cumulative Normal Distribution function coefficients:
// In RPD Version of this function.
//------------------------------------------------------------------------------

const double q_dp = 0.3989422804014;   // = 1.0 / sqrt(2.0 * PI)
const double q_dA1 = 0.2316419;
const double q_dB1 = 0.31938153;
const double q_dB2 = -0.356563782;
const double q_dB3 = 1.781477937;
const double q_dB4 = -1.821255978;
const double q_dB5 = 1.330274429;
const double q_EPS = 3.0e-7;
const double q_FPMIN = 1.0e-30;
const unsigned long q_lMinDate = 0L;
const unsigned long q_lMaxDate = 2000000000L;

//------------------------------------------------------------------------------
// Macro Definitions for random number generation
const unsigned q_MBIG = 1000000000;
const unsigned q_MSEED = 161803398;
const unsigned q_MZ = 0;
const double q_FAC = (1.0 / q_MBIG);
const double q_MAXRAN = 4.294967296e9;


//------------------------------------------------------------------------------
// Date Const's
//------------------------------------------------------------------------------
const unsigned q_MaxNumNextDays = 5;

//------------------------------------------------------------------------------
// Discount Consts
//------------------------------------------------------------------------------
const double q_DfAccuracy = 1e-15;
const unsigned long q_DfMaxIterations = 100;


//------------------------------------------------------------------------------
// Msg's Consts
//-------------------------------------------------------------------------------
const unsigned long q_MsgLen = 255;

//------------------------------------------------------------------------------
// Iteration Consts
//-------------------------------------------------------------------------------
const unsigned long q_ITMAX = 100;

//------------------------------------------------------------------------------
// Optimisation constants
//-------------------------------------------------------------------------------
const unsigned long q_OptInterp = (1 << 0);//位移
const unsigned long q_OptPricing = (1 << 1);
const unsigned long q_OptTree = (1 << 2);

//------------------------------------------------------------------------------
// Unfixed rate marker
//-------------------------------------------------------------------------------
const double q_UnfixedRate = -999.;


// Cash data
#define q_CashOneDay			100
#define q_CashTwoDays			20
#define q_CashThreeDays			3
#define q_CashOneTwoDays		120
#define q_CashOneThreeDays		103
#define q_CashTwoThreeDays		23
#define q_CashOneTwoThreeDays	123


//===============================================================================以下部分为Constants.h=============================================
const double q_DaysPerAnnum = 365.0;
const double daysInAYear = 365.0;

//#define EPS 1.0E-06
#define gSpotShift 0.001
#define VSN 1.0e-8


const double q_SMALL = 1e-8;
const double q_LARGE = 1e+16;
const double q_BGM_TOL = 0.0000001;

const double q_dINVPIP = 0.31830988618379069;   // = 1.0 / pi;
const double q_dINVSQRTPIP = 0.56418958354775628;   // = 1.0 / sqrt(pi)
const double q_dSQRTTWO = 1.4142135623730951;	   // = sqrt(2.0)
const double q_dINVSQRTTWOPIP = 0.398942280401433;     // = 1.0 / sqrt(2.0 * pi)



// volatility returns for swaption pricer
const double q_dNegVol1 = -0.1;
const double q_dNegVol2 = -0.2;
const double q_dNegVol3 = -0.3;
const double q_dNegVol4 = -0.4;

// max number of time steps for the tree
const int q_nMaxNumTreeTimeSteps = 7000;

// minimum days between calibration date and valuation date
const int q_nMinCalibMinusValDays = 10;

// maximum vega constants for swaption pricer
const double q_dMaxVegaError = 0.85;
const double q_dMaxYenVegaError = 0.65;

// limits for analytic integration over Gaussian
const int q_UpperIntegralLimit = 1000;
const int q_LowerIntegralLimit = -1000;

// Acceptable accuracy for TARN
const double q_OneCent = 0.01;

// Acceptable ratio of MC paths to bundles in BGM
const double q_MCPathBundleRatioLimit = 10.;

///////////////////////////////////
// gauss tree constants 

const long q_NUMKVALUES = 500;
const long q_BETAFILEPRECISION = 16;


// acceptable error bounds for Gauss low resolution tree constraints

const double q_ERRBND_LOW_PROB = 1.0e-13;
const double q_ERRBND_LOW_MEAN = 1.0e-11;
const double q_ERRBND_LOW_VAR = 1.0e-11;
const double q_ERRBND_LOW_Q = 1.0e-14;

// acceptable error bounds for Gauss mid resolution tree constraints
const double q_ERRBND_MID_PROB = 1.0e-13;
const double q_ERRBND_MID_MEAN = 1.0e-9;
const double q_ERRBND_MID_VAR = 1.0e-7;
const double q_ERRBND_MID_Q = 1.0e-8;

// end of gauss tree constants
///////////////////////////////////
const int q_ValidDayGap = 5;	// one business week.
// The ordering here IS important: defines the order that
// each event will be handled if multiple events on same date

const long q_mFloat1StartPeriodMask = (1 << 0);		// 1
const long q_mFloat2StartPeriodMask = (1 << 1);		// 2
const long q_mFloatTransferDateMask = (1 << 2);		// 4
const long q_mExerciseFeesDateMask = (1 << 3);		// 8
const long q_mExerciseDateMask = (1 << 4);		// 16
const long q_mNoticeDateMask = (1 << 5);		// 32
const long q_mFixed1CashflowMask = (1 << 6);		// 64
const long q_mFixed1SettingMask = (1 << 7);		// 128
const long q_mMisc1CashflowMask = (1 << 8);		// 256
const long q_mFloat1PaymentDateMask = (1 << 9);		// 512
const long q_mExchange1CashflowMask = (1 << 10);		// 1024
const long q_mFixed2CashflowMask = (1 << 11);		// 2048 
const long q_mMisc2CashflowMask = (1 << 12);		// 4096 
const long q_mFloat2PaymentDateMask = (1 << 13);		// 8192 
const long q_mExchange2CashflowMask = (1 << 14);		// 16384 
const long q_mFixedTransferDateMask = (1 << 15);		// 32768
const long q_mTriggerStartDateMask = (1 << 16);		// 65536
//const long q_mTriggerEndDateMask	= (1<<17);		// 131072

enum class E_LIBORindex
{
	e_1M_LIBOR = 0,
	e_3M_LIBOR = 1,
	e_6M_LIBOR = 2,
	e_12M_LIBOR = 3
};
enum class EModelType
{
	e_HullWhite1F = 0,
	e_BlackKara1F = 1,
	e_BlackYield = 2,
	e_MarkvFunc1F = 3,
	e_HullWhite2F = 4,
	e_BlackKara2F = 5,
	e_MarkvFunc2F = 6,
	e_HWFX_SPT = 7,
	e_HWFX_FUT = 8,
	e_HullWhiteAnalytic = 9,
	e_BlackAnalytic = 10,
	e_BGM = 11,
	e_BGM1F = 12,
	e_BGM2F = 13
};
enum class EPDEProductID
{
	e_PDE1DCallableSwap = 0,
	e_PDE1DNonCallableSwap = 1,
	e_PDE2DCallableSwap = 2,
	e_PDE2DNonCallableSwap = 3,
	e_PDE3DCallableSwap = 4,
	e_PDE3DNonCallableSwap = 5
};
enum class ECalibrateType
{
	e_CalibrateDefault = -1,
	e_CalibrateAll = 0,
	e_CalibrateIR1 = 1,
	e_CalibrateIR2 = 2,
	e_CalibrateFX = 3,
	e_CalibrateNone = 4
};
enum class EGridType
{
	e_TRITREE = 0,
	e_RECTGRID = 1,
	e_PDE = 2,
	e_GSSTREE_LW = 30,
	e_GSSTREE_MD = 50,
	e_GSSTREE_HI = 80,
	e_GSSTREE_SP = 120
};
enum class EStubConv
{
	e_NoChange = 0,
	e_BondStub = 1,
	e_SwapStub = 2
};
enum class EExchangeType
{
	e_QGNone = 0,
	e_QGInitial = 1,
	e_QGFinal = 2,
	e_QGInitialAndFinal = 3
};
enum class EVariableType
{
	e_DiscountFactor1 = 0,
	e_DiscountFactor2 = 1,
	e_OptDiscountFactor1 = 2,
	e_OptDiscountFactor2 = 3,
	e_UnderlyingValue = 4,
	e_OptionValue = 5,
	e_AFSvalue = 6,
	e_PeriodCashflow = 7,
	e_ExerciseFees = 8,
	e_Side1Value = 9,
	e_Side2Value = 10,
	e_TriggerDiscountFactor = 11,
	e_TriggerDiscountFactor2 = 12,
	e_TriggerAccrual = 13,
	e_TriggerSwap = 14,
	e_AFSTriggerSwap = 15,

	e_FlexiCap1 = 21,
	e_FlexiCap2 = 22,
	e_FlexiCap3 = 23,
	e_FlexiCap4 = 24,
	e_FlexiCap5 = 25,
	e_FlexiCap6 = 26,
	e_FlexiCap7 = 27,
	e_FlexiCap8 = 28,
	e_FlexiCap9 = 29,
	e_FlexiCap10 = 30,

	e_FlexiCap11 = 31,
	e_FlexiCap12 = 32,
	e_FlexiCap13 = 33,
	e_FlexiCap14 = 34,
	e_FlexiCap15 = 35,
	e_FlexiCap16 = 36,
	e_FlexiCap17 = 37,
	e_FlexiCap18 = 38,
	e_FlexiCap19 = 39,
	e_FlexiCap20 = 40,

	e_FlexiCap21 = 41,
	e_FlexiCap22 = 42,
	e_FlexiCap23 = 43,
	e_FlexiCap24 = 44,
	e_FlexiCap25 = 45,
	e_FlexiCap26 = 46,
	e_FlexiCap27 = 47,
	e_FlexiCap28 = 48,
	e_FlexiCap29 = 49,
	e_FlexiCap30 = 50,

	e_FlexiCap31 = 51,
	e_FlexiCap32 = 52,
	e_FlexiCap33 = 53,
	e_FlexiCap34 = 54,
	e_FlexiCap35 = 55,
	e_FlexiCap36 = 56,
	e_FlexiCap37 = 57,
	e_FlexiCap38 = 58,
	e_FlexiCap39 = 59,
	e_FlexiCap40 = 60,

	e_FlexiCap41 = 61,
	e_FlexiCap42 = 62,
	e_FlexiCap43 = 63,
	e_FlexiCap44 = 64,
	e_FlexiCap45 = 65,
	e_FlexiCap46 = 66,
	e_FlexiCap47 = 67,
	e_FlexiCap48 = 68,
	e_FlexiCap49 = 69,
	e_FlexiCap50 = 70,

	e_FlexiCap51 = 71,
	e_FlexiCap52 = 72,
	e_FlexiCap53 = 73,
	e_FlexiCap54 = 74,
	e_FlexiCap55 = 75,
	e_FlexiCap56 = 76,
	e_FlexiCap57 = 77,
	e_FlexiCap58 = 78,
	e_FlexiCap59 = 79,
	e_FlexiCap60 = 80,

	e_FlexiCap61 = 81,
	e_FlexiCap62 = 82,
	e_FlexiCap63 = 83,
	e_FlexiCap64 = 84,
	e_FlexiCap65 = 85,
	e_FlexiCap66 = 86,
	e_FlexiCap67 = 87,
	e_FlexiCap68 = 88,
	e_FlexiCap69 = 89,
	e_FlexiCap70 = 90,

	e_FlexiCap71 = 91,
	e_FlexiCap72 = 92,
	e_FlexiCap73 = 93,
	e_FlexiCap74 = 94,
	e_FlexiCap75 = 95,
	e_FlexiCap76 = 96,
	e_FlexiCap77 = 97,
	e_FlexiCap78 = 98,
	e_FlexiCap79 = 99,
	e_FlexiCap80 = 100,

	e_FlexiCap81 = 101,
	e_FlexiCap82 = 102,
	e_FlexiCap83 = 103,
	e_FlexiCap84 = 104,
	e_FlexiCap85 = 105,
	e_FlexiCap86 = 106,
	e_FlexiCap87 = 107,
	e_FlexiCap88 = 108,
	e_FlexiCap89 = 109,
	e_FlexiCap90 = 110,

	e_FlexiCap91 = 111,
	e_FlexiCap92 = 112,
	e_FlexiCap93 = 113,
	e_FlexiCap94 = 114,
	e_FlexiCap95 = 115,
	e_FlexiCap96 = 116,
	e_FlexiCap97 = 117,
	e_FlexiCap98 = 118,
	e_FlexiCap99 = 119,
	e_FlexiCap100 = 120



};
enum  class EInterpType
{
	e_QGLinear = 0,
	e_QGExponential = 1,
	e_QGLogLinear = 2,
	e_QGConstVariance = 3
};
enum class EHWFXModelType
{
	e_SPT = 0,
	e_FUT = 1
};
enum class EConvexityType
{
	e_BRatcliffe = 1,
	e_InHouse = 2
};
template<class T> inline
int sgn(T a)
{
	if (a < 0)
	{
		return -1;
	}

	return 1;
}
// DO NOT DELETE THIS CODE BELOW !!!!!!!!!!!!
// It is used for debugging release code and is uncommented only when needed !!!!!!

//			char buffer[500]; 
//			double aNumber = *pTotNonExValInThisGrid; 
//			double bNumber = *pTotExValInThisGrid; 
//			double cNumber = (double) *pNumPathsInThisGrid; 
//			double dNumber = (double) i; 
//			LPCTSTR Astring = "    "; 
//			sprintf_s ( buffer, "\t %f \t %f \t %f \t %f \n", aNumber, bNumber, cNumber, dNumber ); 
//			OutputDebugString( buffer ); 



//===================================================以下来自于multiType.h============================================================
namespace multi 
{				// Multi asset options.

	typedef enum {				// Contract types for historic compatibility with MultiAsset().
		basketAsian = 0,
		worstLookback = 3
	} Payoff;

	typedef enum class Model_ {
		// Single vol models:
		V1_shortTail = 0,	// 2 point fwd, vol*sqrt(1-2/3*(T1-T0)/T1).
		V1_MM3 = 1,	// moment matching, vol*sqrt(1-2/3*(T1-T0)/T1).
		V1_MMg = 2,	// moment matching, vol of geometric  mean.
		V1_MMa = 3,	// moment matching, vol of arithmetic mean.
		V1_BBg = 4,	// Brownian bridge, vol of geometric  mean.
		V1_BBa = 5,	// Brownian bridge, vol of arithmetic mean.
		V1_nstep = 6,	// N step asian.
		V1_GC = 7,	// Condition on geometric means.
		V1_BBa2 = 8,	// BBa with approximate SD to run faster.
		V1_corrPay = 9,	// Correlated payoff.

		// Skew models:
		localVol = 100,	// Short step Monte Carlo.
		copula = 101,	// "Copula" technique for joint distribution of stock prices.
		GC = 102,	// Geometric conditional.
		GCgrid = 103,	// Geometric conditional on a grid.  Slower but more accurate for no vol skew.
		copulaB = 104,	// Correlated Monte Carlo for barrier & LB.
		bvol = 105	// Basket vol.
	} Model;

	typedef enum class MC_{				// Monte Carlo methods.
		sobol = 0,
		ran1 = 1,
		ran2 = 2,
		ran3 = 3
	} MC;

	class Param {				// Model parameters.
	public:
		Param(void) : model(Model::V1_shortTail), mc(MC::sobol), Nmc(0), Nt(0), Ns(0), corrSkew(0), yld(0), CV(0), smooth(0) {}
		Param(int Nt_, int Ns_) : model(Model::V1_shortTail), mc(MC::sobol), Nmc(0), Nt(Nt_), Ns(Ns_), corrSkew(0), yld(0), CV(0), smooth(0) {}
		Model	model;
		MC		mc;				// Random number generator.
		int		Nmc;			// Number of MC paths.
		int		Nt;				// Number of time steps per year.
		int		Ns;				// Size of spot grid.
		double	corrSkew;		// Correlation skew?
		int		yld;			// Dividend method:  0: cash, 1: convert to continuous yield, 2: convert to discrete yield.
		int		CV;				// 1: Control variate.  0: none.
		double	smooth;			// Amount of smoothing.
	};
};
//===================================================以下来自于multiType.h============================================================
