/*
 *  列主元gauss消去求解a[][] * x[] = b[]
 *  返回是否有唯一解，若有解在b[]中
 */
#define fabs(x) ((x) > 0 ? (x) : (-x))
#define eps 1e-10

const int MAXN = 100;

int gaussCpivot(int n, double a[][MAXN], double b[])
{
    int i, j, k, row = 0;
    double MAXP, temp;
    for (k = 0; k < n; k++)
    {
        for (MAXP = 0, i = k; i < n; i++)
        {
            if (fabs(a[i][k]) > fabs(MAXP))
            {
                MAXP = a[row = i][k];
            }
        }
        if (fabs(MAXP) < eps)
        {
            return 0;
        }

        if (row != k)
        {
            for (j = k; j < n; j++)
            {
                temp = a[k][j];
                a[k][j] = a[row][j];
                a[row][j] = temp;
                temp = b[k];
                b[k] = b[row];
                b[row] = temp;
            }
        }
        for (j = k + 1; j < n; j++)
        {
            a[k][j] /= MAXP;
            for (i = k + 1; i < n; i++)
            {
                a[i][j] -= a[i][k] * a[k][j];
            }
        }
        b[k] /= MAXP;
        for (i = n - 1; i >= 0; i--)
        {
            for (j = i + 1; j < n; j++)
            {
                b[i] -= a[i][j] * b[j];
            }
        }
    }

    return 1;
}

/*
 *  全主元gauss消去解a[][] * x[] = b[]
 *  返回是否有唯一解，若有解在b[]中
 */
#define fabs(x) ((x) > 0 ? (x) : (-x))
#define eps 1e-10

const int MAXN = 100;

int gaussTpivot(int n, double a[][MAXN], double b[])
{
    int i, j, k, row = 0, col = 0, index[MAXN];
    double MAXP, temp;
    for (i = 0; i < n; i++)
    {
        index[i] = i;
    }
    for (k = 0; k < n; k++)
    {
        for (MAXP = 0, i = k; i < n; i++)
        {
            for (j = k; j < n; j++)
            {
                if (fabs(a[i][j] > fabs(MAXP)))
                {
                    MAXP = a[row = i][col = j];
                }
            }
        }
        if (fabs(MAXP) < eps)
        {
            return 0;
        }

        if (col != k)
        {
            for (i = 0; i < n; i++)
            {
                temp = a[i][col];
                a[i][col] = a[i][k];
                a[i][k] = temp;
            }
            j = index[col];
            index[col] = index[k];
            index[k] = j;
        }
        if (row != k)
        {
            for (j = k; j < n; j++)
            {
                temp = a[k][j];
                a[k][j] = a[row][j];
                a[row][j] = temp;
            }
            temp = b[k];
            b[k] = b[row];
            b[row] = temp;
        }
        for (j = k + 1; j < n; j++)
        {
            a[k][j] /= MAXP;
            for (i = k + 1; i < n; i++)
            {
                a[i][j] -= a[i][k] * a[k][j];
            }
        }
        b[k] /= MAXP;
        for (i = k + 1; i < n; i++)
        {
            b[i] -= b[k] * a[i][k];
        }
    }
    for (i = n - 1; i >= 0; i--)
    {
        for (j = i + 1; j < n; j++)
        {
            b[i] -= a[i][j] * b[j];
        }
    }
    for (k = 0; k < n; k++)
    {
        a[0][index[k]] = b[k];
    }
    for (k = 0; k < n; k++)
    {
        b[k] = a[0][k];
    }

    return 1;
}

//  高斯消元法求方程组的解

const int MAXN = 300;
//  有equ个方程，var个变元。增广矩阵行数为equ，列数为var＋1，分别为0到var
int equ, var;
int a[MAXN][MAXN];  //  增广矩阵
int x[MAXN];        //  解集
int free_x[MAXN];   //  用来存储自由变元（多解枚举自由变元可以使用）
int free_num;       //  自由变元的个数

//  返回值为－1表示无解，为0是唯一解，否则返回自由变元个数
int Gauss()
{
    int max_r, col, k;
    free_num = 0;
    for (k = 0, col = 0; k < equ && col < var; k++, col++)
    {
        max_r = k;
        for (int i = k + 1; i < equ; i++)
        {
            if (abs(a[i][col]) > abs(a[max_r][col]))
            {
                max_r = i;
            }
        }
        if (a[max_r][col] == 0)
        {
            k--;
            free_x[free_num++] = col;   //  这是自由变元
            continue;
        }

        if (max_r != k)
        {
            for (int j = col; j < var + 1; j++)
            {
                swap(a[k][j], a[max_r][j]);
            }
        }
        for (int i = k + 1; i < equ; i++)
        {
            if (a[i][col] != 0)
            {
                for (int j = col; j < var + 1; j++)
                {
                    a[i][j] ^= a[k][j];
                }
            }
        }
    }
    for (int i = k; i < equ; i++)
    {
        if (a[i][col] != 0)
        {
            return -1;  //  无解
        }
    }

    if (k < var)
    {
        return var - k; //  自由变元个数
    }

    //  唯一解，回代
    for (int i = var - 1; i >= 0; i--)
    {
        x[i] = a[i][var];
        for (int j = i + 1; j < var; j++)
        {
            x[i] ^= (a[i][j] && x[j]);
        }
    }

    return 0;
}

