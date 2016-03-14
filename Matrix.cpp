#include<iostream>
#include<cstdlib>//调用内存分配函数calloc和malloc
#include<cstring>//调用拷贝函数memcpy(void* des,void*src,const int count),并返回指向备份区的指针
using namespace std;

class Matrix 
{
private:
	int row;//矩阵的行
	int column;//矩阵的列
	double **p;//指向矩阵的二级指针
	void allocate_memory()//申请矩阵空间
	{
		if(row<=0||column<=0)
		{
			cout<<"ERROR:can't allocate momory!"<<endl;
			return;
		}
		p=(double**)malloc(row*sizeof(double*));//使用一个二级指针实现对矩阵的内存分配
		p[0]=(double*)calloc(row*column,sizeof(double));
		for(int i=1;i<row;i++)
		{
			p[i]=p[0]+column*i;
			//p[i]=p[i-1]+column;
		}
		return;
	}
	
	//重载allocate_memory函数
	//带有参数的内存申请，m*n的double数据
	void allocate_memory(const int m,const int n)
	{
		if(m<=0||n<=0)
		{
			cout<<"ERROR:can't allocate momory!"<<endl;
			return;
		}
		p=(double**)malloc(m*sizeof(double*));//使用一个二级指针实现对矩阵的内存分配
		p[0]=(double*)calloc(m*n,sizeof(double));
		for(int i=1;i<m;i++)
		{
			p[i]=p[0]+n*i;
			//p[i]=p[i-1]+n;
		}
		return;
		
	}
	void release_memory()//释放矩阵空间
	{
		if(p[0]!=NULL)
			free(p[0]);
		if(p!=NULL)
			free(p);
		return;
	}
public:
	//关键字return不可以使用在构造或析构函数中；即使使用return不返回数据，也是不可以，会报错；
	Matrix():row(0),column(0),p(NULL)		{}//空矩阵
	Matrix(const int m,const int n):row(m),column(n)//分配M*N的矩阵空间
	{
		if(m<=0||n<=0)
		{
			cout<<"ERROR:"<<endl;
			exit(0);
		}
		allocate_memory();//分配M*N的矩阵空间
	}
	
	//将从指针指向p的地址开始的p_num个元素复制给当前m*n矩阵对象
	Matrix(const int m,const int n,double* const p_,const int p_num):row(m),column(n)
	{//固定m,n的值为常量；固定指针p_为常量，始终指向一个地址；
		//p_++;//这是不允许的，不符合语法规则；
		if(m*n<p_num)
		{
			cout<<"ERROR:can't copy!"<<endl;
			exit(0);//退出程序
		}
		int k=0;
		allocate_memory();
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<column;j++)
				p[i][j]=p_[k++];
			if(k==p_num)
					break;
		}
	}
	
	//将矩阵M拷贝给当前矩阵;copy constructor
	Matrix(const Matrix& M)//使用引用可以节省创建新对象占用的空间
	{
		row=M.row;
		column=M.column;//两个赋值语句将M矩阵的行列个数拷贝给当前矩阵
		//cout<<row<<' '<<column<<endl;
		allocate_memory(row,column);
		/*
		for(int i=0;i<row;i++)
			for(int j=0;j<column;j++)
				p[i][j]=M.p[i][j];
		*/
		memcpy(p[0],M.p[0],row*column*sizeof(double));
	}
	~Matrix()//析构，释放矩阵空间
	{
		release_memory();
	}
	void show()//显示矩阵元素
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<column;j++)
				cout<<p[i][j]<<' ';
			cout<<endl;
		}
	}
	
};

int main()
{
	Matrix A(3,4);
	A.show();
	cout<<"======"<<endl;
	double arr[6]={1,2,3,4,5};
	Matrix B(4,2,arr,6);
	B.show();
	cout<<"======"<<endl;
	Matrix C(B);
	C.show();
}