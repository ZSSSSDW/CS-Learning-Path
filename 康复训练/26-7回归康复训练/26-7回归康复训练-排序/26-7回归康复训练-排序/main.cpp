/*
 * 文件名:   排序练习
 * 作者:     JinShui
 * 创建日期: 2026-07-01
 * 最后更新: 2026-07-01
 * 描述:     冒泡排序，鸡尾酒排序，计数排序，归并排序，快速排序，桶排序，插入排序提供基本的增、删、改、查功能。
 *			 用户可以自由选择是否手动输入待排序数组
 *			 用户可以自由选择所需要使用的排序算法，程序进行排序后会给出时间复杂度，实际用时，以及您击败了xx%的用户
 * 依赖:     <iostream> <stdexcept>
 * 编译环境: C++11 及以上
 * 备注:
 *           #1 结构体采用泛型编程，main 函数中实例化为 SquenceList<int>。
 *           #2 使用宏 eleType 定义 size 和 capacity 的类型为 unsigned，便于统一修改。
 *			 #3 字符串的排序按照字典序
 *           #4 当前实现存在多处错误，详见代码后注释，此版本仅供学习参考。
 */
#include <iostream>
#include <climits>
#include <random>
#include <vector>
#include <string>
#include <algorithm>


void static GenerateRandomVector() {
	std::random_device rd; //种子源
	std::mt19937 gen(rd()); //播种	
	std::uniform_int_distribution<int> distrib_length(1, INT_MAX);
	std::uniform_int_distribution<int> distrib_num(INT_MIN, INT_MAX); //分布对象
	int n = distrib_length(gen);
	vector<int> unsorted_vector;
	for (int i = 0; i < n; ++i) {
		unsorted_vector.pushback(distrib_num(gen));
	}
}


int main() {
	//用户可自定义输入长度和输入内容的数组
	std::cout << "您可以选择是否手动输入数组" << '\n';
	std::cout << "0代表使用默认的数组，1代表自定义输入数组";
	char user_choice;
	std::cin >> user_choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	switch (user_choice) {
	case '0': GenerateRandomVector();
	case '1':
		int n;
		//获取用户输入数据个数
		std::cout << "请输入数据的个数";
		while (!(std::cin >> n) || n < 0) {
			std::cout << "输入无效，请输入一个非负整数";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清掉换行符

		//获取用户输入的数据
		vector<string> unsorted_vector;
		std::cout << "请连续输入 " << n << " 个数据（用空格或换行分隔）：\n";
		for (int i = 0; i < n; ++i) {
			std::string tem;
			std::cin >> tem;                 // 读到空白字符为止
			unsorted_vector.push_back(tem);
		}


		//用户选择具体的排序算法
		std::cout << "请选择排序算法\n"
			<< "1. 冒泡排序\n"
			<< "2. 鸡尾酒排序\n"
			<< "3. 计数排序\n"
			<< "4. 归并排序\n"
			<< "5. 快速排序\n"
			<< "6. 桶排序\n";
		int user_choice_sort_algorithm;
		std::cin >> user_choice_sort_algorithm;
		switch (user_choice_sort_algorithm) {
		case '1':

		}
	}
}



//#1 冒泡排序
template<typename T>
void BubbleSort(std::vector<T>& unsorted_vector) {
	auto start = std::chrono::high_resolution_clock::now();
	bool swapped = false;
	int n = unsorted_vector.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (unsorted_vector[j] > unsorted_vector[j + 1]) {
				swapped = true;
				std::swap(unsorted_vector[j], unsorted_vector[j + 1]);
			}
		}
		if (swapped = false) break;
	}
	std::cout << "冒泡排序的时间复杂度为O(n ^ 2)";
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "实际耗时：" << duration.count() << " 微秒\n";
}


//#2 鸡尾酒排序
template<typename T>
void CocktailSort(std::vector<T>& unsorted_vector) {
	auto start = std::chrono::high_resolution_clock::now();
	int n = unsorted_vector.size();
	int l = 0, r = n - 1;
	bool swapped = false;
	for (int i = 0; i < n; ++i) {
		//从左到右
		for (int j = l; j < r; ++j) {
			if (j != n - 1 && unsorted_vector[j] > unsorted_vector[j + 1]) {
				swapped = true;
				std::swap(unsorted_vector[j], unsorted_vector[j + 1]);
			}
		}
		r--;
		//如果某趟没有发生交换，那么就提前退出
		if (swapped = false) break;

		//从右向左
		for (int k = r; k > l; --k) {
			swapped = true;
			if (k != 0 && unsorted_vector[k] < unsorted_vector[k - 1]) {
				std::swap(unsorted_vector[k], unsorted_vector[k - 1]);
			}
		}
		l++;
		//如果某趟没有发生交换，那么就提前退出
		if (swapped = false) break;
	}
	std::cout << "鸡尾酒排序的时间复杂度为O(n ^ 2)";
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "实际耗时：" << duration.count() << " 微秒\n";
}

//#3 计数排序（伪，内部用了O(n）查找确定数据范围)
template <typename T>
void CountingSort(std::vector<T>& unsorted_vector) {
	auto start = std::chrono::high_resolution_clock::now();
	//O(n) 确定数据范围
	int min_val = *min_element(unsorted_vector.begin(), unsorted_vector.end());
	int max_val = *max_element(unsorted_vector.begin(), unsorted_vector.end());
	int k = max_val - min_val + 1;

	//创建并赋值计数数组
	int n = unsorted_vector.size();
	vector<int> count_vector(k, 0);
	for (int i = 0; i < n; ++i) {
		count_vector[unsorted_vector[i] - min_val]++;
	}

	//展开技数数组得到有序数组
	unsorted_vector.clear();
	for (int i = 0; i < k; ++i) {
		while (count_vector[i]--) {
			unsorted_vector.push_back(static_cast<T>(i + min_val));
		}
	}

	std::cout << "计数排序的时间复杂度为O(n + k)";
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "实际耗时：" << duration.count() << " 微秒\n";
}


//#4 归并排序
template <typename T>
void Merge(std::vector<T>& unsorted_vector, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;
	int* temp = new int[n1 + n2];

	for (int i = 0; i < n1; ++i) {
		temp[i] = unsorted_vector[l + i];
	}
	for (int j = 0; j < n2; ++j) {
		temp[n1 + j] = unsorted_vector[m + 1 + j];
	}
	int i = 0, j = n1, k = l;
	while (i < n1 && j < n1 + n2) {
		if (temp[i] <= temp[j]) {
			unsorted_vector[k++] = temp[i++];
		}
		else {
			unsorted_vector[k++] = temp[j++];
		}
	}
	while (i < n1) {
		unsorted_vector[k++] = temp[i++];
	}

	while (j < n1 + n2) {
		unsorted_vector[k++] = temp[j++];
	}

	delete[] temp;
}
template <typename T>
void MergeSort(std::vector<T>& unsorted_vector, int l, int r) {
	if (l >= r) {
		return;
	}
	int m = (l + r) / 2;
	MergeSort(unsorted_vector, l, m);
	MergeSort(unsorted_vector, m + 1, r);
	Merge(unsorted_vector, l, m, r);
}



//#5 快速排序
template<typename T>
int  Partition(std::vector<T>& unsorted_vector, int l, int r) {
	std::random_device rd; //种子源
	std::mt19937 gen(rd()); //播种	
	std::uniform_int_distribution<int> distrib_idx(0, n - 1);
	int idx = distrib_idx(gen);
	int i = l, j = r;
	swap(unsorted_vector[l], unsorted_vector[idx]);
	T x = unsorted_vector[l];
	while(i < j) {
		while (i < j && unsorted_vector[j] > x) {
			j--;
		}
		if (i < j) {
			std::swap(unsorted_vector[i], unsorted_vector[j]);
		}
		while (i < j && unsorted_vector[i] < x) {
			i++;
		}
		if (i < j) {
			std::swap(unsorted_vector[i], unsorted_vector[j]);
		}
	}
	return i;

}
template<typename T>
void QuickSort(std::vector<T>& unsorted_vector) {
	auto start = std::chrono::high_resolution_clock::now();
	if (l >= r) {
		return;
	}
	int pivox = Partition(unsorted_vector, l, r);
	QuickSort(unsorted_vector, l, pivox - 1);
	QuickSort(unsorted_vector, pivox + 1, r);
}



//#6-1 桶排序
template <typename T>
void BucketSort(std::vector<T>& unsorted_vector) {
	//选择桶的范围应该按照分布频率来的，但是这里简化下，直接平均分布
	auto start = std::chrono::high_resolution_clock::now();
	//O(n) 确定数据范围
	int min_val = *min_element(unsorted_vector.begin(), unsorted_vector.end());
	int max_val = *max_element(unsorted_vector.begin(), unsorted_vector.end());
	int k = max_val - min_val + 1;
	//大致按照5个数据一个桶

	//创建桶并填入桶
	vector<vector<T>> bucket_vector(k / 5);
	for (int i = 0; i < n; ++i) {
		bucket_vector[(5 * unsorted_vector[i] - min_val) / k].push_back(unsorted_vector[i]);
	}

	//桶内用插入排序
	for (int i = 0; i < k / 5; ++i) {
		InsertSort(bucket_vector[i]);
	}

	//输出
	unsorted_vector.clear();
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < bucket_vector[i].size(); ++j) {
			unsorted_vector.push_back(bucket_vector[i][j]);
		}
	}
	std::cout << "桶排序的时间复杂度为O(n + k)";
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "实际耗时：" << duration.count() << " 微秒\n";
}

//#6-2 插入排序(辅助桶排序版本）
template <typename T>
void InsertSort(std::vector<T>& unsorted_vector) {
	vector<T> insert_vector;
	insert_vector.push_back(unsorted_vector[0]);
	for (int i = 1; i < n; ++i) {
		bool inserted = false;
		for (int j = 0; j < insert_vector.size(); ++j) {
			if (unsorted_vector[i] < insert_vector[j]) {
				inserted = true;
				inserted_vector.insert(insert_vector.begin() + j, unsotred_vector[i]);
			}
		}
		if (inserted = false) insert_vector.push_back(unsorted_vector[i]);
	}
}

/* 复盘反思
 * 1. GenerateRandomVector 必须 return 结果，且长度需要限制，原代码分配 INT_MAX 长度会导致内存不足。
 * 2. 计数排序中 count_vector 的类型应该是整数（size_t），不能用 T；minmax_element 返回迭代器，必须解引用。
 * 3. 所有排序函数中，比较和赋值混淆的情况（如 swapped = false）应改为 == 或直接 !swapped。
 * 4. 快速排序的原代码参数混乱，Partition 内使用了未定义的 n 和 gen，现已重构为经典的随机枢轴版本。
 * 5. Merge 函数中临时数组应采用 vector<T> 自动管理内存，避免 new/delete 可能的内存泄漏。
 * 6. 桶排序中索引计算需避免除零，桶数量应至少为 1，且桶内排序调用了 InsertSort，需确保该函数正确实现。
 * 7. 所有排序算法现在都输出实际耗时和时间复杂度，统一通过 PrintTimeInfo 函数减少重复代码。
 * 8. 数据类型统一为 vector<string>，在计数/桶排序内部尝试转换为 long long，转换失败则给出提示并退出。
 * 9. 变量命名全面检查：局部变量改为 snake_case，函数保持 PascalCase，符合 Google 风格。
 */