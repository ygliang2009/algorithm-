/*
 * @author:chemical.liang
 * @version:1.0
 * @date: 2012-10-30
 * @desc: 数独游戏 
 * 	 (c++ version)
 */

const int DIM_NUM = 9;

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using std::vector;
using std::cout;
using std::pair;
using std::ostream_iterator;

/* 调用STL中的全排列函数进行遍列，获得可以填充到每个行列中的备选队列 */
vector<vector<int> > get_permutation(vector<int> in_row)
{
	vector<vector<int> > ret_array;
	do{
		ret_array.push_back(in_row);
	}while(next_permutation(in_row.begin(),in_row.end()));
	
	return ret_array;
}

/* 获取每个行列中的备选数组 */
vector<int> get_backnum(vector<int> in_row)
{
	vector<int> ret_vec;
	vector<int> ret_tmp(DIM_NUM,-1);
	for(int i = 0; i < in_row.size(); i++)
		if(in_row[i] != -1)
			ret_tmp[in_row[i]-1] = 1;
	for(int i = 0; i < DIM_NUM; i++)
		if(ret_tmp[i] != 1)
			ret_vec.push_back(i+1);
	return ret_vec;
}

class SD
{
	/*
	 * 内部枚举类，标志是行或列
	 */
	enum MatrixT
	{
		ROW = 0, COL
	};
	public:
		void parse_data();
		void parse_row(vector<vector<int> >&,vector<pair<vector<vector<int> >,vector<vector<int> > > >,int);
		SD(vector<vector<int> > matrix);
		/* description:
		 * 	为行和列填充数据
		 *	@param:data 被填充容器
		 *	@param:fd  填充容器
		 *	@param:m_type 填充类型，是填充行还是填充列
		 */
		static bool fill_data(vector<vector<int> >&data,int idx,vector<int> fd,MatrixT m_type)
		{
			int k = 0;
			if(m_type == ROW)
			{
				for(int i = 0; i < DIM_NUM; i++)
					if(data[idx][i] == -1)
					{
						if(find(data[idx].begin(),data[idx].end(),fd[k]) != data[idx].end())
							data[idx][i] = fd[k++];
						else
							return false;
					}
				return true;
			}
			else if(m_type == COL){
				vector<int> col_array;
				for(int i = 0; i < DIM_NUM; i++)
					col_array.push_back(data[i][idx]);
				for(int i = 0; i < DIM_NUM; i++)
					if(data[i][idx] == -1)
					{
						if(find(col_array.begin(),col_array.end(),fd[k]) != col_array.end())
							 
							data[i][idx] = fd[k++];
						else
							return false;
					}
				return true;
			}
		}
	private:
		static const int dim = 9;
		vector<pair<vector<vector<int> > ,vector<vector<int> > > > perm_array;
		vector<vector<int> > data;
};
 

SD::SD(vector<vector<int> > matrix):data(matrix)
{
	/* 初始化全排列数组 */
	for(int i = 0; i < data.size(); i++)
	{
		vector<int> vec_row = get_backnum(data[i]);
		vector<vector<int> > perm_row = get_permutation(vec_row);
		vector<int> vec_col_tmp;
		for(int j = 0; j < data.size(); j++)
			vec_col_tmp.push_back(data[j][i]);
		vector<int> vec_col = get_backnum(vec_col_tmp);
		vector<vector<int> > perm_col = get_permutation(vec_col);
		perm_array.push_back(pair<vector<vector<int> >,vector<vector<int> > >(perm_row,perm_col));
	} 
}

void SD::parse_data()
{
	if(data.size() == 0)
		return;
	parse_row(data,perm_array,0);		
}

/*
 * @param data: 数独数组
 * @param perm_array: 全排列数组
 * @param i: 当前遍历到的数独指针
 * @param idx_r: 当前遍历到行的全排列指针
 * @param idx_c: 当前遍历到列的全排列指针
 */
void SD::parse_row(vector<vector<int> >& data,vector<pair<vector<vector<int> > ,vector<vector<int> > > > perm_array,int i)
{
	if(i == DIM_NUM)
		return;
	
	/* 根据当前的排列指针确定当前需要填充的排列 */
	for(int i = 0; i < DIM_NUM; i++){
		vector<int> row_arr = (perm_array[i].first)[i];
		vector<int> col_arr = (perm_array[i].second)[i];
	
		if(fill_data(data,i,row_arr,ROW) && fill_data(data,i,col_arr,COL))
		{
			/* 如果本行填充成功，则继续递归填充下面的行 */
			i++;
			parse_row(data,perm_array,i);
		}
		else{
			/* 否则，回溯到上一行，继续找下面的排列填充 */
			continue;
		}
	}
}

int main()
{
	/* 
	 * To be tested：
	 *    data need be filled with -1 if no data from 1~9
	 */

	vector<vector<int> > data;
	SD sd(data);
	sd.parse_data();
	vector<int> data_2;
	vector<int> back_vec = get_backnum(data_2);
	copy(back_vec.begin(),back_vec.end(),ostream_iterator<int>(cout,"\n"));
	return 0;
}
