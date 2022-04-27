#include <iostream>
#include <iomanip>

using namespace std;

class Mat
{
    
private:
  uint16_t mCols;
  uint16_t mRows;
  double * mData;
  
public:

 Mat ()
  {
    mCols = 0;
    mRows = 0;
    mData = nullptr;
  }
  
    Mat (uint16_t mRows, uint16_t mCols)
  {
    this->mRows = mRows;
    this->mCols = mCols;
    mData = new double[mRows * mCols];
  }
  Mat (uint16_t mCols)
  {
    this->mCols = mCols;
    mRows = 1;
    mData = new double[mRows * mCols];
  }
 
  Mat (const Mat & mat)
  {
    mCols = mat.mCols;
    mRows = mat.mRows;
    mData = mat.mData;
  }
  
  
  Mat operator+ (const Mat & other)
  {
    Mat res (mRows, mCols);
    if (mCols == other.mCols && mRows == other.mRows)
      {
	for (unsigned int i = 0; i < mRows * mCols; i++)
	  {
	    res.mData[i] = mData[i] + other.mData[i];
	  }
	return res;
      }
    return Mat (0, 0);
  }
  Mat operator* (const Mat & other)
  {
    Mat res (mRows, mCols);
    if (mCols == other.mCols && mRows == other.mRows)
      {
	for (unsigned int i = 0; i < mRows * mCols; i++)
	  {
	    res.mData[i] = mData[i] * other.mData[i];
	  }
	return res;
      }
    return Mat (0, 0);
  }

  Mat operator^ (const Mat & other)
  {
    Mat res (mRows, other.mCols);
    double m1[mRows][mCols], m2[other.mRows][other.mCols], m3[mRows][other.mCols];
    for (unsigned int i = 0; i < mRows; i++)
      {
	for (unsigned int j = 0; j < other.mCols; j++)
	  {
	    m3[i][j] = 0;
	  }
    }
	for (unsigned int i = 0; i < mRows; i++)
	  {
	    for (unsigned int j = 0; j < mCols; j++)
	      {
		m1[i][j] = mData[i * mCols + j];
	      }

	  }
	for (unsigned int i = 0; i < other.mRows; i++)
	  {
	    for (unsigned int j = 0; j < other.mCols; j++)
	      {
		m2[i][j] = other.mData[i * other.mCols + j];
	      }

	  }
	for (unsigned int i = 0; i < mRows; i++)
	  {

	    for (unsigned int j = 0; j < other.mCols; j++)
	      {
		for (unsigned int k = 0; k < mCols; k++)
		  {
		    m3[i][j] += m1[i][k] * m2[k][j];
		  }

	      }
	  }
	for (unsigned int i = 0; i < mRows; i++)
	  {
	    for (unsigned int j = 0; j < other.mCols; j++)
	      {
		res.mData[i * other.mCols + j] = m3[i][j];
	      }
	  }
	return res;
      
  }
      uint16_t getCols ()
  {
    return mCols;
  }
  uint16_t getRows ()
  {
    return mRows;
  }
  double getValue (uint16_t i, uint16_t j)
  {
    return mData[i * mCols + j];
  }
  void setValue (uint16_t i, uint16_t j, double val)
  {
    mData[i * mCols + j] = val;
  }
  
    ~Mat ()
    {
      mData = NULL;
      delete[]mData;
    }
  };


  int main ()
  {
    double s = 0, result = 0;
    double temp;
    uint16_t mR, mC, nR, nC;
    cin >> mR >> mC >> nR >> nC;
    Mat M (mR, mC);
    Mat N (nR, nC);
    for (uint16_t i = 0; i < M.getRows (); i++)
      {
	for (uint16_t j = 0; j < M.getCols (); j++)
	  {
	    cin >> temp;
	    M.setValue (i, j, temp);
	  }
      }
    for (uint16_t i = 0; i < N.getRows (); i++)
      {
	for (uint16_t j = 0; j < N.getCols (); j++)
	  {
	    cin >> temp;
	    N.setValue (i, j, temp);
	  }
      }
    Mat R (M.getRows (), N.getCols ());
    if (M.getCols () == N.getRows ())
      {
	R = M ^ N;
      }
    else
      {
	R = M * N + N;
      }
    for (uint16_t i = 0; i < R.getRows (); i++)
      {
	for (uint16_t j = 0; j < R.getCols (); j++)
	  s += R.getValue (i, j);
      }
    result = s / (R.getRows () * R.getCols ());

    //cout << setprecision (2) << result;
    printf("%.2lf", result);

    return 0;
  }
