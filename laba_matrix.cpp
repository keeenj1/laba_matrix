#include <iostream>
#include <vector>
#include <array>
#include <random>

struct matrix {
	int** data_ = nullptr;
	size_t n_ = 0u;
	size_t m_ = 0u;
};

void print(matrix& print_mat) {
	for (int i = 0; i < print_mat.n_;i++) {
		for (int j = 0;j < print_mat.m_;j++) {
			std::cout << print_mat.data_[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void construct(matrix& out, size_t n, size_t m) {
	out.n_ = n;
	out.m_ = m;
	out.data_ = new int* [n];
	for (int i = 0; i < n; i++) {
		out.data_[i] = new int[m];
	}
	for (int i = 0; i < n;i++) {
		for (int j = 0;j < m;j++) {
			out.data_[i][j] = 0;
		}
	}
}
void destruct(matrix& in) {
	for (int i = 0;i < in.n_;i++) {
		delete[]in.data_[i];
	}
	delete[]in.data_;
}
matrix copy(const matrix& mat) {
	matrix copy;
	construct(copy,mat.n_,mat.m_);
	for (int i = 0; i < mat.n_;i++) {
		for (int j = 0; j < mat.m_;j++) {
			copy.data_[i][j] = mat.data_[i][j];
		}
	}
	return copy;
}
matrix add(const matrix& mat, const matrix& mat1) {
	matrix sum;
	construct(sum,mat.n_,mat.m_);
	if (mat.n_ != mat1.n_ || mat.m_ != mat1.m_) {
		matrix empty;
		return empty;
	}
	else {
		for (int i = 0;i < mat.n_;i++) {
			for (int j = 0; j < mat.m_;j++) {
				sum.data_[i][j] = mat.data_[i][j] + mat1.data_[i][j];
			}
		}
	}
	return sum;
}
matrix sub(const matrix& mat, const matrix& mat1) {
	matrix razn;
	construct(razn, mat.n_, mat.m_);
	if (mat.n_ != mat1.n_ || mat.m_ != mat1.m_) {
		matrix empty;
		return empty;
	}
	else {
		for (int i = 0;i < mat.n_;i++) {
			for (int j = 0; i < mat.m_;j++) {
				razn.data_[i][j] = mat.data_[i][j] - mat1.data_[i][j];
			}
		}
	}
	return razn;
}
matrix mult(const matrix& mat, const matrix& mat1) {
	if (mat.n_ == mat1.m_ && mat.m_ == mat1.n_) {
		matrix proiz;
		construct(proiz, mat.m_, mat1.n_);
		for (int i = 0;i < proiz.m_;i++) {
			for (int j = 0;j < proiz.n_;j++) {
				for (int k = 0; k < mat.n_;k++) {
					proiz.data_[i][j] += mat.data_[i][k] * mat1.data_[k][j];
				}
			}
		}
		return proiz;
	}
	return matrix();
}
void transposition(matrix& mat) {
	matrix mat_trans;
	construct(mat_trans, mat.m_, mat.n_);
	for (int i = 0;i < mat.n_;i++) {
		for (int j = 0;j < mat.m_;j++) {
			mat_trans.data_[i][j] = mat.data_[j][i];
		}
	}
	destruct(mat);
	mat = mat_trans;
}
int main()
{
	int a, b;
	std::cin >> a >> b;
	matrix mat;
	matrix mat1;
	construct(mat, a, b);
	construct(mat1, a, b);
	matrix mat_copy = copy(mat); print(mat_copy);
	matrix mat_add = add(mat, mat1); print(mat_add);
	matrix mat_proiz = mult(mat, mat1); print(mat_proiz);
	return 0;
}