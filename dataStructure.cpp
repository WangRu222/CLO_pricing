#include"dataStructure.h"


ostream& operator<<(ostream& os, const Array1D& tThis)
{
	for (size_t i = 0; i < tThis.size(); i++)
	{
		os << tThis[i] << ", ";
	}
	os << "\n";
	return os;
}
ostream& operator<<(ostream& os, const Array2D& tThis)
{
	for (size_t i = 0; i < tThis.size(); i++)
	{
		for (size_t j = 0; j < tThis[i].size(); j++)os << tThis[i][j] << ", ";
		os << "\n";
	}
	//os << "\n";
	return os;
}


//-----------以下三个函数在QFrequency中用到------
//本身定义在Utility.h/.cpp中，为了不在次引入，在此就单独定义了三个函数
void  ToUpper(string& s)
{
	string::iterator p = s.begin();
	while (p != s.end())
	{
		*p = toupper(*p);//单个字符转化为大写
		++p;
	}
}
void ToLower(string& s)
{
	string::iterator p = s.begin();
	while (p != s.end())
	{
		*p = tolower(*p);//单个字符转化为小写
		++p;
	}
}
//匹配部分字符串
size_t  MatchPS(const char* szPermittedString[], unsigned int nNumPermitted, const char* szPartialString, size_t& nMatchedIndex)
{
	// First, lets look for an exact match
	for (nMatchedIndex = 0; nMatchedIndex < nNumPermitted; nMatchedIndex++)
	{
		if (strcmp(szPermittedString[nMatchedIndex], szPartialString) == 0)
		{
			return 1;
		}
	}

	// No exact match, lets do the best we can
	size_t nMatches(0);
	size_t nStringLen = strlen(szPartialString);
	for (size_t nIndex(0); nIndex < nNumPermitted; nIndex++)
	{
		if (strncmp(szPermittedString[nIndex], szPartialString, nStringLen) == 0)
		{   // A partial match
			nMatches++;
			nMatchedIndex = nIndex;
		}
	}

	return nMatches;
}

//template<class Type>
//void tvec<Type>::push_back(Type v0)
//{
//	resize(n + 1);//长度增加一
//	p[n - 1] = v0;
//}
//
//template<class Type>
//void tvec<Type>::pop_first()
//{
//	Type* p0;
//	int n0;
//	if (n == 1) { delete[] p; n = 0; }
//	else(n > 1)
//	{
//		n0 = n - 1;
//		p0 = new Type[n0];
//		for (int i = 0; i < n0; i++)p0[i] = p[i + 1];
//		delete[] p;
//		p = p0;
//		n = n0;
//	}
//}

//定义一些关于Array2D的函数=========
double dot(const Array1D& a1, const Array1D& a2)//向量点击
{
	size_t n1 = a1.size(), n2 = a2.size();
	if (n1 != n2)throw"can not do array dot!!!";
	else
	{
		double sum0 = 0.0;
		for (int k = 0; k < n1; k++)sum0 = sum0 + a1[k] * a2[k];
		return sum0;
	}
}
Array2D dot(const Array2D& m1, const  Array2D& m2)//矩阵乘积
{
	size_t r1 = m1.size(), c1 = m1[0].size(), r2 = m2.size(), c2 = m2[0].size();
	if (c1 != r2)throw"can not do matrix dot!!!";
	else
	{
		Array2D res;
		res.resize(r1);
		for (int i = 0; i < r1; i++)
		{
			res[i].resize(c2);
			for (int j = 0; j < c2; j++)
			{
				double sum0 = 0.0;
				for (int k = 0; k < c1; k++)sum0 = sum0 + m1[i][k] * m2[k][j];
				res[i][j] = sum0;
			}
		}
		return res;
	}
}
Array1D dot(const Array2D& m1, const Array1D& a1)
{
	size_t r1 = m1.size(), c1 = m1[0].size(), r = a1.size();
	if (c1 != r)throw"can not do matrix dot!!!";
	else
	{
		Array1D res;
		res.resize(r1);
		for (int i = 0; i < r1; i++)
		{
			double sum0 = 0.0;
			for (int k = 0; k < c1; k++)sum0 = sum0 + m1[i][k] * a1[k];
			res[i] = sum0;
		}
		return res;
	}

}
Array1D dot_element(const Array1D& a1, const  Array1D& a2)
{
	size_t n1 = a1.size(), n2 = a2.size();
	if (n1 != n2)throw"different length of tow Array!!!";
	Array1D res(n1);
	for (int i = 0; i < n1; i++) res[i] = a1[i]*a2[i];
	return res;
}
Array1D plus_element(const Array1D& a1, const  Array1D& a2)
{
	size_t n1 = a1.size(), n2 = a2.size();
	if (n1 != n2)throw"error: different size!!!";
	Array1D res(a1.size());
	for (int i = 0; i < n1; i++)res[i] = a1[i] + a2[i];
	return res;
}
Array2D plus_element(const Array2D& m1, const  Array2D& m2)
{
	size_t r1 = m1.size(), c1 = m1[0].size(), r2 = m2.size(), c2 = m2[0].size();
	if (r1 != r2 || c1 != c2)throw"different size of two matrix!!";
	else
	{
		Array2D res(r1);
		for (int i = 0; i < c1; i++)
		{
			res[i].resize(c1);
			for (int j = 0; j < c1; j++)res[i][j] = m1[i][j] +m2[i][j];
		}
		return res;
	}
}
Array2D dot_element(const Array2D& m1, const  Array2D& m2)
{
	size_t r1 = m1.size(), c1 = m1[0].size(), r2 = m2.size(), c2 = m2[0].size();
	if (r1 != r2 || c1 != c2)throw"different size of two matrix!!";
	else
	{
		Array2D res(r1);
		for (int i = 0; i < c1; i++)
		{
			res[i].resize(c1);
			for (int j = 0; j < c1; j++)res[i][j] = m1[i][j] * m2[i][j];
		}
		return res;
	}
}
Array2D dot_element(const Array2D& m1, double x)
{
	Array2D res = m1;
	for (int i = 0; i < m1.size(); i++)
	{
		for (int j = 0; j < m1[i].size(); j++)res[i][j] = res[i][j] * x;
	}
	return res;
}
Array2D trans(const Array2D& m)
{
	size_t r = m.size(), c = m[0].size();
	for (int i = 1; i < r; i++)if (m[i].size() != c)throw"can not be transposed!!!";

	Array2D res;
	res.resize(c);
	for (int i = 0; i < c; i++)
	{
		res[i].resize(r);
		for (int j = 0; j < r; j++)res[i][j] = m[j][i];
	}
	return res;

}
Array1D minus_Array1D(const Array1D& first, const  Array1D& second)
{
	size_t n1 = first.size(), n2 = second.size();
	if (n1 != n2)throw"different length of tow Array!!!";
	Array1D res(n1);
	for (int i = 0; i < n1; i++) res[i] = first[i] - second[i];
	return res;
}
double sum_Array1D(const Array1D& first)
{
	size_t n = first.size();
	if (n == 0) return 0;
	else
	{
		double sum0 = 0.0;
		for (int i = 0; i < n; i++)sum0 += first[i];
		return sum0;
	}
}
double trace_Array2D(const Array2D& m)
{
	size_t c = m.size(), r = m[0].size();
	if (c != r)throw"rows != columns";
	else 
	{
		double sum0 = 0;
		for (int i = 0; i < c; i++)sum0 = sum0 + m[i][i];
		return sum0;

	}
}
Array1D getPart_Array1D(Array1D& originalArr, size_t begIndex, size_t endIndex)
{
	//返回【begIndex,endIndex)之间的元素
	size_t n = originalArr.size();

	if (begIndex > endIndex && endIndex >= 0)throw"error: begIndex > endIndex!!!";
	else if(begIndex < 0)throw"error: begIndex <0 !!!";
	
	if (endIndex < 0)
	{
		endIndex = endIndex + n;//-1变为n-1
		if(begIndex > endIndex) throw"error: begIndex > endIndex!!!";
	}

	Array1D res(endIndex - begIndex + 1);
	for (size_t i = 0; i < res.size(); i++)res[i] = originalArr[begIndex + i];
	return res;
}
Array2D getPart_Array2D(Array2D& originalArr, size_t begIndex, size_t endIndex)
{
	//返回【begIndex,endIndex)之间的元素
	size_t n = originalArr.size();
	

	if (begIndex > endIndex && endIndex >= 0)throw"error: begIndex > endIndex!!!";
	else if (begIndex < 0)throw"error: begIndex <0 !!!";

	if (endIndex < 0)
	{
		endIndex = endIndex + n;//-1变为n-1
		if (begIndex > endIndex) throw"error: begIndex > endIndex!!!";
	}

	Array2D res(endIndex - begIndex + 1);
	for (size_t i = 0; i < res.size(); i++)
	{
		size_t m = originalArr[begIndex+i].size();
		res[i].resize(m);
		for(int j = 0; j <m;j++)res[i][j] = originalArr[begIndex + i][j];
	}
	return res;
}

double getNorm2(Array1D& arr)
{
	if (arr.size() == 0) return 0;
	else
	{
		double normv = 0;
		for (size_t i = 0; i < arr.size(); i++)normv += pow(abs(arr[i]), 2);
		return sqrt(normv);
	}
}

double maxDiag(Array2D& arr2d)
{
	double v0 = -1e10;
	for (size_t i = 0; i < arr2d.size(); i++)
		if (arr2d[i][i] > v0)
			v0 = arr2d[i][i];

	return v0;
	
}

//---------------------dvec内部成员函数定义------------------------------
dvec::dvec(const Array1D& a) : tvec<double>(static_cast<int>(a.size())) {
	//printf("using copy constructor(Array1D)\n");
	for (int i = 0; i < n; i++) (*this)[i] = a[i];
}

dvec::dvec(const dvec& a) : tvec<double>(static_cast<int>(a.n)) {
	//printf("using copy constructor(Array1D)\n");
	for (int i = 0; i < n; i++) (*this)[i] = a[i];
}
dvec::dvec(const Array2D& a) : tvec<double>(static_cast<int>(a.size()* a[0].size())) {
	int		Nr = static_cast<int>(a.size());
	int		Nc = static_cast<int>(a[0].size());
	int		i, j;
	for (i = 0; i < Nr; i++) {
		for (j = 0; j < Nc; j++) (*this)[Nc * i + j] = a[i][j];
	}
}

double dvec::sum()
{
	double sum0 = 0;
	for (int i = 0; i < n; i++) sum0 = sum0+(*this)[i];
	return sum0;
}

ostream& operator<<(ostream& os, const dvec& tThis)
{
	for (size_t i = 0; i < tThis.n; i++)
	{
		os << tThis[i] << ", ";
	}
	os << "\n";
	return os;
}

//---------------------ivec内部成员函数定义------------------------------
ivec::ivec(const Array1I& a) : tvec<int>(static_cast<int>(a.size())) {
	for (int i = 0; i < n; i++) (*this)[i] = (int)a[i];
}

ivec::ivec(const Array2I& a) : tvec<int>(static_cast<int>(a.size()* a[0].size())) {
	int		Nr = static_cast<int>(a.size());
	int		Nc = static_cast<int>(a[0].size());
	int		i, j;
	for (i = 0; i < Nr; i++) {
		for (j = 0; j < Nc; j++) (*this)[Nc * i + j] = a[i][j];
	}
}

//---------------------cvec内部成员函数定义------------------------------
void cvec::append(const char* s) {
	size_t		l0 = p ? strlen(p) : 0; //原字符串长度
	size_t		l1 = strlen(s);//需要添加的字符串长度
	l0 = MAX(MIN(n, l0),0); //l0,n一般情况是相同的
	l0 = MAX(0, MIN(MAX_STR / 2 - 1, l0));
	l1 = MAX(0, MIN(MAX_STR / 2 - 1, l1));
	resize(l0 + l1 + 1); //先扩展cvec对象中的字符串的长度，空缺位置先补0
	if (p + l0 == 0)throw"error address!!!";
	else strncpy(p + l0, s, l1); //将来源字符串s中的l1个长度的字符，复制到p字符串中位置为l0开始的地方；并在末尾补\0;
	p[l0 + l1] = '\0';

}

//-------------------imat内部成员函数定义-------------------------------
void imat::resize(int r0, int c0) {
	int		i, j;
	int* p0 = new int[static_cast<size_t>(r0*c0)];
	for (i = 0; i < MIN(r, r0); i++) {
		for (j = 0; j < MIN(c, c0); j++) p0[c0 * i + j] = (*this)[i][j];//相同的位置保持原值
		for (j = MIN(c, c0); j < c0; j++) p0[c0 * i + j] = 0;//增加列，均赋值0；缩减列，不执行
	}
	for (i = MIN(r, r0); i < r0; i++) for (j = 0; j < c0; j++) p0[c0 * i + j] = 0;//增加行，均赋值0；减小行，不执行
	delete[] p;
	p = p0;
	r = r0;
	c = c0;
}

imat& imat::operator=(const imat& mat)
{
	//int r;
	//int c;
	resize(mat.r, mat.c);
	for (int i = 0; i < mat.r; i++)
		for (int j = 0; j < mat.c; j++)(*this)[i][j] = mat[i][j];// p[i * mat.r + j] = mat.p[i * mat.r + j];
	return *this;
}

imat::imat(const imat& mat) : r(mat.r), c(mat.c), p(new int[static_cast<size_t>(mat.r*mat.c)])
{
	for (int i = 0; i < mat.r; i++)
		for (int j = 0; j < mat.c; j++)
			//p[i * mat.c + j] = mat.p[i * mat.c + j];
			(*this)[i][j] = mat[i][j];//以上两种方式均可以
}


//-------------------dmat内部成员函数定义--------------------------------
dmat::dmat(const Array2D& a) : r(static_cast<int>(a.size())), c(r <= 0 ? 0 : static_cast<int>(a[0].size())), p(new double[r * c]) {
	for (size_t i = 0; i < r; i++) for (size_t j = 0; j < c; j++) (*this)[i][j] = a[i][j]; //this代表当前class的具体的某个类对象。能够使用[i][j]
};
void dmat::resize(size_t r0, size_t c0)
{
	size_t		i, j;
	double* p0 = new double[r0 * c0];
	for (i = 0; i < MIN(r, r0); i++) {
		for (j = 0; j < MIN(c, c0); j++) p0[c0 * i + j] = (*this)[i][j];//相同的位置保持原值
		for (j = MIN(c, c0); j < c0; j++) p0[c0 * i + j] = 0;//增加列，均赋值0；缩减列，不执行
	}
	for (i = MIN(r, r0); i < r0; i++) for (j = 0; j < c0; j++) p0[c0 * i + j] = 0;//增加行，均赋值0；减小行，不执行
	delete[] p;
	p = p0;
	r = r0;
	c = c0;
}
// i -> i*r mod r*c-1.
void dmat::transpose(void) {
	double	temp;
	if (r > 1 && c > 1) {
		size_t		n = r * c - 1;
		size_t		i;
		dvec	q(r * c);
		for (i = 0; i < r * c; i++) q[i] = p[i];
		for (i = 1; i < n; i++)
			p[i] = q[(i * c) % n];
	}
	temp = r; r = c; c = temp;
}
dmat& dmat::operator=(const dmat& mat)
{
	//printf("Assignment Operator Overloading\n");
	//int r;
	//int c;
	if (r != mat.r || c != mat.c) {
		//printf("resize\n");
		resize(mat.r, mat.c);
	}
	for (size_t i = 0; i < mat.r; i++)
		for (size_t j = 0; j < mat.c; j++)(*this)[i][j] = mat[i][j];// p[i * mat.r + j] = mat.p[i * mat.r + j];
	return *this;
}
dmat& dmat::operator=(const Array2D& x)
{
	//int r;
	//int c;
	resize(x.size(), x[0].size());
	for (size_t i = 0; i < x.size(); i++)
		for (size_t j = 0; j < x[0].size(); j++)(*this)[i][j] = x[i][j];// p[i * mat.r + j] = mat.p[i * mat.r + j];
	return *this;
}
dmat::dmat(const dmat& mat) : r(mat.r), c(mat.c), p(new double[static_cast<size_t>(mat.r * mat.c)])
{
	//printf("Copy Constructor\n");
	for (size_t i = 0; i < mat.r; i++)
		for (size_t j = 0; j < mat.c; j++)
			//p[i * mat.c + j] = mat.p[i * mat.c + j];
			(*this)[i][j] = mat[i][j];//以上两种方式均可以
}
Array1D dmat::row(size_t _r) const//获取第_r行的值
{
	if (_r < 0 || _r >= r)throw"Row_index_out_of_range";
	Array1D vnew(0.0,c);
	for (size_t j = 0; j < c; j++) {
		vnew[j] = (*this)[_r][j];
	}
	return vnew;
}
Array1D dmat::col(size_t _c) const//获取第_c列的值
{
	if (_c < 0 || _c >= c)throw"Column_index_out_of_range";
	Array1D vnew(0.0, r);
	for (size_t i = 0; i < r; i++) {
		vnew[i] = (*this)[i][_c];
	}
	return vnew;
}
double dmat::norm(int _n)
{

	if (r == 1 && c >= 1)//行向量
	{
		if (_n == 1)
		{
			double normv = 0;
			for (size_t i = 0; i < c; i++)normv += abs((*this)[0][i]);
			return normv;
		}
		else if (_n == 2)
		{
			double normv = 0;
			for (size_t i = 0; i < c; i++)normv += pow(abs((*this)[0][i]), 2);
			return sqrt(normv);
		}
		else if (_n == positiveinf)
		{
			double normv = abs((*this)[0][0]);
			for (size_t i = 1; i < c; i++)if(abs((*this)[0][i])>normv) normv = abs((*this)[0][i]);
			return normv;
		}
		else if (_n == negativeinf)
		{
			double normv = abs((*this)[0][0]);
			for (size_t i = 1; i < c; i++)if (abs((*this)[0][i]) < normv) normv = abs((*this)[0][i]);
			return normv;
		}
		else
			throw"not_support_this_Norm!!!";
	}
	else if (r >= 1 && c == 1)//列向量
	{
		if (_n == 1)
		{
			double normv = 0;
			for (size_t i = 0; i < r; i++)normv += abs((*this)[i][0]);
			return normv;
		}
		else if (_n == 2)
		{
			double normv = 0;
			for (size_t i = 0; i < r; i++)normv += pow(abs((*this)[i][0]), 2);
			return sqrt(normv);
		}
		else if (_n == positiveinf)
		{
			double normv = abs((*this)[0][0]);
			for (size_t i = 1; i < r; i++)if (abs((*this)[i][0]) > normv) normv = abs((*this)[i][0]);
			return normv;
		}
		else if (_n == negativeinf)
		{
			double normv = abs((*this)[0][0]);
			for (size_t i = 1; i < r; i++)if (abs((*this)[i][0]) < normv) normv = abs((*this)[i][0]);
			return normv;
		}
		else
			throw"not_support_this_Norm!!!";
	}
	else
		throw"not_support_this_Norm!!!";//矩阵范数暂不支持
	
}
double dmat::maxDiag()
{
	if (rows() != cols())throw"rows_not_euqal_to_cols!!!";
	size_t rs = rows();
	double maxDiag = 0.0;
	if (rs == 0) return maxDiag;
	if (rs == 1) maxDiag = p[0];
	for (size_t i = 1; i < rs; i++)
		if ((*this)[i][i] > maxDiag) maxDiag = (*this)[i][i];
	return maxDiag;
}
double dmat::operator()(size_t _r, size_t _c)
{
	if (_r < 0 || _r >= r)throw"Row_index_out_of_range";
	if (_c < 0 || _c >= c)throw"Column_index_out_of_range";
	return row(_r)[_c];
}
const double dmat::operator()(size_t _r, size_t _c) const
{
	if (_r < 0 || _r >= r)throw"Row_index_out_of_range";
	if (_c < 0 || _c >= c)throw"Column_index_out_of_range";
	return row(_r)[_c];
}
dmat& dmat::operator=(double dVal)
{
	for (size_t i = 0; i < r * c; i++) p[i] = dVal;
	return *this;
}
bool dmat::operator==(const dmat& cThat) const
{
	if (c != cThat.c || r != cThat.r) return false;

	bool bIsEqual = true;
	long n(0);
	for (n = 0; n < size(); n++)
	{
		if (abs(p[n] - cThat.p[n]) > EPS)return bIsEqual = false;
	}
	return bIsEqual;
}
bool dmat::isSizeEqual(dmat& x)
{
	if (c == x.c && r == x.r) return true;
	else return false;

}
dmat& dmat::operator+=(dmat& x)
{
	if (isSizeEqual(x) == false) throw"matrix_size_not_equal!!!";
	for (size_t i = 0; i < r * c; i++) p[i] = p[i] + x.p[i];
	return *this;
}
dmat& dmat::operator-=(dmat& x)
{
	if (isSizeEqual(x) == false) throw"matrix_size_not_equal!!!";
	for (size_t i = 0; i < r * c; i++) p[i] = p[i] - x.p[i];
	return *this;
}
dmat& dmat::operator*=(dmat& x)
{
	if (isSizeEqual(x) == false) throw"matrix_size_not_equal!!!";
	for (size_t i = 0; i < r * c; i++) p[i] = p[i] * x.p[i];
	return *this;
}
dmat& dmat::operator/=(dmat& x)
{
	if (isSizeEqual(x) == false) throw"matrix_size_not_equal!!!";
	for (size_t i = 0; i < r * c; i++) p[i] = p[i] / x.p[i];
	return *this;
}

dmat matrix_Product(dmat& left, dmat& right)
{
	if (left.cols() != right.rows())throw"cannot_do_matrix_product!!!";
	dmat res(left.rows(), right.cols());
	for (size_t i = 0; i < res.rows(); i++)
		for (size_t j = 0; j < res.cols(); j++)
		{
			double temp = 0.0;
			Array1D left_row = left.row(i), right_col = right.col(j);
			for (size_t k = 0; k < left_row.size(); k++)
				temp += left_row[k] * right_col[k];
			res.p[i * res.cols() + j] = temp;
		}
	return res;
}
dmat operator*(dmat& left, dmat& right)
{
	if (left.cols() != right.rows())throw"cannot_do_matrix_product!!!";
	dmat res(left.rows(), right.cols());
	for (size_t i = 0; i < res.rows(); i++)
		for (size_t j = 0; j < res.cols(); j++)
		{
			double temp = 0.0;
			Array1D left_row = left.row(i), right_col = right.col(j);
			for (size_t k = 0; k < left_row.size(); k++)
				temp += left_row[k] * right_col[k];
			res.p[i * res.cols() + j] = temp;
		}
	return res;
}
dmat dot_Product(dmat& left, dmat& right)
{
	if (left.isSizeEqual(right) == false)throw"matrix_size_not_equal!!!";
	dmat res(left.rows(), left.cols());
	for (size_t i = 0; i < res.rows(); i++)
		for (size_t j = 0; j < res.cols(); j++)
		{
			res.p[i * res.cols() + j] = left(i, j) * right(i, j);
		}
	return res;
}
dmat transpose(dmat& x)//调用赋值构造函数吗？
{
	size_t xr = x.rows(), xc = x.cols();
	dmat res(xc,xr);//参数构造函数
	for (size_t i = 0; i < xr; i++)
		for (size_t j = 0; j < xc; j++)
			res[j][i] = x[i][j];
	
	return res;

}
dmat operator-(dmat& left, dmat& right)//矩阵元素相减
{
	dmat res(left.rows(), left.cols());//
	//dmat res = left;//copy constructor
	if (left.isSizeEqual(right) == false) throw"matrix_size_not_equal!!!";
	size_t lr = left.rows(), lc = left.cols();
	for (size_t i = 0; i < lr * lc; i++) res.p[i] = left.p[i] - right.p[i];
	//printf("%f\n", res.p[0]);
	return res;//return res时，超出范围, 调用析构函数，不允许返回局部变量的引用
}
dmat operator+(dmat& left, dmat& right)//矩阵元素相加
{
	dmat res(left.rows(), left.cols());//
	//dmat res = left;
	if (left.isSizeEqual(right) == false) throw"matrix_size_not_equal!!!";
	size_t lr = left.rows(), lc = left.cols();
	for (size_t i = 0; i < lr * lc; i++) res.p[i] = left.p[i] + right.p[i];
	return res;
}
dmat operator*(double x,dmat& left)
{
	dmat res(left.rows(), left.cols());//
	//dmat res = left;
	size_t lr = left.rows(), lc = left.cols();
	for (size_t i = 0; i < lr * lc; i++) res.p[i] = left.p[i]*x;
	return res;

}
dmat operator/(dmat& left, dmat& right)//矩阵元素相除
{
	if (left.isSizeEqual(right) == false)throw"matrix_size_not_equal!!!";
	dmat res(left.rows(), left.cols());
	for (size_t i = 0; i < res.rows(); i++)
		for (size_t j = 0; j < res.cols(); j++)
		{
			res.p[i * res.cols() + j] = left(i, j) / right(i, j);
		}
	return res;
}
dmat operator-(dmat& left, double x)
{
	dmat res(left.rows(), left.cols());
	//dmat res = left;
	size_t lr = left.rows(), lc = left.cols();
	for (size_t i = 0; i < lr * lc; i++) res.p[i] = left.p[i] - x;
	return res;
}
ostream& operator<<(ostream& os, const dmat& tThis)
{
	for (size_t i = 0; i < tThis.rows(); i++)
	{
		for (size_t j = 0; j < tThis.cols(); j++)os << tThis(i,j)<<", ";
		os << "\n";
	}
	os << "---------------\n";
	return os;
}

//====================================================================================
/* allocate a double matrix */
double** New2DMatrix(long nrow, long ncol)
{
	double** m;

	/* allocate pointers to rows */
	m = new double* [nrow];

	/* allocate rows and set pointers to them */
	m[0] = new double[nrow * ncol];
	for (size_t i = 1; i < nrow; i++)
	{
		m[i] = m[i - 1] + ncol;
	}
	return m;
}

void Delete2DMatrix(double** m)
{
	delete[] m[0];
	delete[] m;
}





//-----------------dmatv内部成员函数定义--------------------------------
dmatV::dmatV(int n_, const Array2D** mat) : n(n_), p(new const dmat* [n]) {
	//开辟n个长度的空间，每个里面放dmat的指针，也就是放dmat对象地址
	//p[i]里面存放的是地址，谁的地址呢？一个dmat对象的地址。p[i] = new dmat(*mat[i])//*mat[i]表示的是Array2D对象
	size_t		i, j;
	for (i = 0; i < n; i++) 
	{
		if (!mat || !mat[i]) { p[i] = 0; continue; }
		int	done = 0;
		for (j = 0; !done && j < i; j++) {
			if (mat[j] == mat[i]) {// 表示的是如果mat的连续两个地址指向了同一个Array2D对象的话，就不用开辟新空间了，而是用后面的p[i]指向前面p[j]指向的相同的对象
				p[i] = p[j];
				done = 1;
			}
		}
		if (done) continue;
		//		dmat	Mi(*mat[i]);	// For UNIX compiler 13-jul-04.
		//		p[i]= new dmat(Mi);
		p[i] = new dmat(*mat[i]);//调用dmat的构造函数，
	}
}

dmatV::~dmatV(void) {
	size_t		i, j;
	if (p) {
		for (i = 0; i < n; i++) {
			if (!p[i]) continue;
			int	later = 0;
			for (j = i + 1; !later && j < n; j++) if (p[j] == p[i]) later = 1;
			if (later) continue;
			delete p[i];//因为在构造函数中使用了两个层次的new,所以在析构函数中，同样需要有两个层次的delete
		}
	}
	delete[] p;
}