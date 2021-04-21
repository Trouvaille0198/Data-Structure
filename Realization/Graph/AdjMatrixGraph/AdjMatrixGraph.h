#ifndef ADJ_MATRIX_GRAPH
#define ADJ_MATRIX_GRAPH
#include <bits/stdc++.h>
#include "../../SeqList/SeqList.h"
using namespace std;

const int DEFAULT_SIZE = 100;
const int DEFAULT_INFINITY = 1000;
//图的邻接矩阵类
template <class ElemType, class WeightType>
class AdjMatrixGraph
{
protected:
    int _vexMaxNum, _arcNum;     // 最大顶点数, 边数
    int *_tag;                   // 标志数组
    SeqList<ElemType> _vertexes; // 顶点数组
    int **_arcs;                 // 邻接矩阵, 二维数组
    int _dirType;                // 有向图或无向图
    int _weightType;             // 带权值或不带权值
    WeightType _infinity;

public:
    AdjMatrixGraph(int dirType = 0, int weightType = 0,
                   int vexMaxNum = DEFAULT_SIZE, WeightType infinity = DEFAULT_INFINITY); //默认构造函数
    AdjMatrixGraph(ElemType *es, int vexNum,
                   int dirType = 0, int weightType = 0,
                   int vexMaxNum = DEFAULT_SIZE, WeightType infinity = DEFAULT_INFINITY); //构造函数
    ~AdjMatrixGraph();
    void Clear();
    bool IsEmpty();
    int GetVexNum() const;                          // 求顶点个数
    int GetArcNum() const;                          // 求边数
    int GetOrder(ElemType vex) const;               // 求顶点序号
    ElemType GetElem(int index) const;              // 求指定下标的顶点值
    void SetElem(int index, ElemType vex);          // 更新指定下标的顶点值
    int FirstAdjVex(int v) const;                   // 求v的第一个邻接点的下标
    int NextAdjVex(int v1, int v2) const;           // 求v1相对于v2的下一个邻接点的下标
    void InsertVex(const ElemType &vex);            // 插入顶点
    void InsertArc(int v1, int v2, int weight = 1); // 插入边
    void DeleteVex(const ElemType &vex);            // 删除顶点
    void DeleteArc(int v1, int v2);                 // 删除边
    WeightType GetWeight(int v1, int v2) const;     // 求从顶点为v1到v2的边的权值
    void SetWeight(int v1, int v2, WeightType w);   // 设置从顶点为v1到v2的边的权值
    int GetTag(int v) const;                        // 求顶点v的标志值
    void SetTag(int v, int value);                  // 设置顶点v的标志值
    void Display() const;                           // 打印图
    void SetArcs(int **arcs, int vexNum);           // 设置新的邻接矩阵
    void Dijkstra(int v);                           //迪杰斯特拉算法
};

template <class ElemType, class WeightType>
AdjMatrixGraph<ElemType, WeightType>::AdjMatrixGraph(int dirType, int weightType, int vexMaxNum, WeightType infinity)
{
    if (vexMaxNum < 0)
    {
        cout << "允许的顶点最大数目不能为负!" << endl;
        return;
    }
    _dirType = dirType;
    _weightType = weightType;
    _arcNum = 0;
    _vexMaxNum = vexMaxNum;
    _infinity = infinity;

    _vertexes = SeqList<ElemType>(vexMaxNum);
    _tag = new int[vexMaxNum];
    _arcs = (int **)new int *[vexMaxNum];
    for (int i = 0; i < vexMaxNum; i++)
    //构造邻接矩阵
    {
        _arcs[i] = new int[vexMaxNum];
    }
}

template <class ElemType, class WeightType>
AdjMatrixGraph<ElemType, WeightType>::AdjMatrixGraph(ElemType *es, int vexNum,
                                                     int dirType, int weightType,
                                                     int vexMaxNum, WeightType infinity)
{
    if (vexMaxNum < 0)
    {
        cout << "允许的顶点最大数目不能为负!" << endl;
        return;
    }
    if (vexMaxNum < vexNum)
    {
        cout << "顶点数目不能大于允许的顶点最大数目!" << endl;
        return;
    }
    _arcNum = 0;
    _vexMaxNum = vexMaxNum;
    _dirType = dirType;
    _weightType = weightType;
    _infinity = infinity;

    _vertexes = SeqList<ElemType>(es, vexNum, vexMaxNum);
    _tag = new int[vexMaxNum];
    _arcs = (int **)new int *[vexMaxNum];

    for (int i = 0; i < vexMaxNum; i++)
    //构造邻接矩阵
    {
        _arcs[i] = new int[vexMaxNum];
    }
    for (int i = 0; i < vexMaxNum; i++)
    //赋零值
    {
        _tag[i] = 0;
        for (int j = 0; j < vexMaxNum; j++)
        {
            _arcs[i][j] = _infinity;
        }
    }
}

template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::Clear()
//边数，顶点数清零
{
    _arcNum = 0;
    _vertexes.ClearList();
}
template <class ElemType, class WeightType>
bool AdjMatrixGraph<ElemType, WeightType>::IsEmpty()
//判断顶点数是否等于零
{
    return _vertexes.GetLength() == 0;
}

template <class ElemType, class WeightType>
AdjMatrixGraph<ElemType, WeightType>::~AdjMatrixGraph()
{
    //顺序表应该会自己析构掉
    delete[] _tag;
    for (int i = 0; i < _vexMaxNum; i++) // 释放邻接矩阵的行
        delete[] _arcs[i];
    delete[] _arcs; // 释放邻接矩阵
}
template <class ElemType, class WeightType>
int AdjMatrixGraph<ElemType, WeightType>::GetVexNum() const
{
    return _vertexes.GetLength();
}
template <class ElemType, class WeightType>
int AdjMatrixGraph<ElemType, WeightType>::GetArcNum() const
{
    return _arcNum;
}
template <class ElemType, class WeightType>
int AdjMatrixGraph<ElemType, WeightType>::GetOrder(ElemType vex) const
{
    return _vertexes.LocateElem(vex);
}
template <class ElemType, class WeightType>
ElemType AdjMatrixGraph<ElemType, WeightType>::GetElem(int index) const
{
    return _vertexes.GetElem(index);
}
template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::SetElem(int index, ElemType vex)
{
    _vertexes.SetElem(index, vex);
}
template <class ElemType, class WeightType>
int AdjMatrixGraph<ElemType, WeightType>::FirstAdjVex(int v) const
{
    if (v < 0 || v > _vexMaxNum)
    {
        cout << "v 不合法!" << endl;
        return NULL;
    }
    int row = v; //顶点在顶点集的位置，即顶点在邻接矩阵中行的位置
    for (int col = 0; col < _vertexes.GetLength(); col++)
    {

        if (_arcs[row][col] != _infinity)
            return col;
    }
    return -1; //无邻接点
}

template <class ElemType, class WeightType>
int AdjMatrixGraph<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
{
    if (v1 < 0 || v1 > _vexMaxNum || v2 < 0 || v2 > _vexMaxNum || v1 == v2)
    {
        cout << "v1不合法!" << endl;
        return NULL;
    }
    if (v2 < 0 || v2 > _vexMaxNum || v1 == v2)
    {
        cout << "v2不合法!" << endl;
        return NULL;
    }
    if (v1 == v2)
    {
        cout << "v1不可等于v2!" << endl;
        return NULL;
    }
    int row = v1; //顶点在顶点集的位置，即顶点在邻接矩阵中行的位置
    for (int col = v2 + 1; col < _vertexes.GetLength(); col++)
    //循环从v2的后一个顶点开始
    {

        if (_arcs[row][col] != _infinity)
            return col;
    }
    return -1; //无邻接点
}
template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::InsertVex(const ElemType &vex)
{
    int _vexNum = _vertexes.GetLength();
    if (_vexNum == _vexMaxNum)
    {
        cout << "图已满，不可再插入顶点!" << endl;
        return;
    }
    _vertexes.InsertElem(vex);
    _tag[_vexNum] = 0;
    for (int i = 0; i < _vexNum + 1; i++)
    {
        _arcs[_vexNum][i] = _infinity; //新增一行
        _arcs[i][_vexNum] = _infinity; //新增一列
    }
}
template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::InsertArc(int v1, int v2, int weight)
{
    if (_weightType == 0)
        // 若为无权图, 插入的权值强制为 1
        weight = 1;
    int _vexNum = GetVexNum();
    if (v1 < 0 || v1 >= _vexNum || v2 < 0)
    {
        cout << "v1不合法!" << endl;
        return;
    }
    if (v2 < 0 || v2 >= _vexNum)
    {
        cout << "v2不合法!" << endl;
        return;
    }
    if (v1 == v2)
    {
        cout << "v1不可等于v2!" << endl;
        return;
    }

    if (_arcs[v1][v2] == _infinity)
    {
        _arcs[v1][v2] = weight;
        if (_dirType == 0)
            // 若为无向图, 对称处也设边
            _arcs[v2][v1] = weight;
        _arcNum++;
    }
}
template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::DeleteVex(const ElemType &vex)
{
    int i = _vertexes.LocateElem(vex); //找到vex在顶点集中的位置
    if (i == -1)
    {
        cout << "找不到要删除的点!" << endl;
        return;
    }
    //删除关联边
    for (int j = 0; j < _vertexes.GetLength(); j++)
    {
        if (_arcs[i][j] != _infinity)
        {
            _arcNum--;
            _arcs[i][j] = _infinity;
            if (_dirType == 0)
                // 若为无向图, 对称处也删边
                _arcs[j][i] = _infinity;
        }
    }
    int _vexNum = _vertexes.GetLength() - 1; //记录删点后顶点的个数
    if (i < _vexNum)
    //若待删除点的位置不在最后，将最后的顶点前移
    {
        //顶点集前移
        _vertexes.SetElem(i, _vertexes.GetElem(_vexNum));
        _vertexes.DeleteElemByIndex(_vexNum);
        //标志集前移
        _tag[i] = _tag[_vexNum];
        //邻接矩阵前移
        for (int col = 0; col <= _vexNum; col++)
            _arcs[i][col] = _arcs[_vexNum][col]; //删行
        for (int row = 0; row <= _vexNum; row++)
            _arcs[row][i] = _arcs[row][_vexNum]; //删列
    }
}
template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::DeleteArc(int v1, int v2)
{
    if (v1 < 0 || v1 > _vexMaxNum || v2 < 0 || v2 > _vexMaxNum || v1 == v2)
    {
        cout << "v1不合法!" << endl;
        return;
    }
    if (v2 < 0 || v2 > _vexMaxNum || v1 == v2)
    {
        cout << "v2不合法!" << endl;
        return;
    }
    if (v1 == v2)
    {
        cout << "v1不可等于v2!" << endl;
        return;
    }
    if (_arcs[v1][v2] != _infinity)
    {
        _arcNum--;
        _arcs[v1][v2] = _infinity;
        if (_dirType == 0)
            // 若为无向图, 对称处也删边
            _arcs[v2][v1] = _infinity;
    }
}
template <class ElemType, class WeightType>
int AdjMatrixGraph<ElemType, WeightType>::GetTag(int v) const
{
    if (v < 0 || v > _vexMaxNum)
    {
        cout << "v 不合法!" << endl;
        return NULL;
    }
    return _tag[v];
}
template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::SetTag(int v, int value)
{
    if (v < 0 || v > _vexMaxNum)
    {
        cout << "v 不合法!" << endl;
        return;
    }
    _tag[v] = value;
}

template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::Display() const
{
    string ref = "0";
    if (_dirType == 1)
        ref = "∞";
    for (int i = 0; i < _vertexes.GetLength(); i++)
    {
        cout << "\t" << _vertexes.GetElem(i);
    }
    cout << endl;

    for (int row = 0; row < _vertexes.GetLength(); row++)
    {
        cout << _vertexes.GetElem(row);
        for (int col = 0; col < _vertexes.GetLength(); col++)
        {
            if (col == row)
                cout << "\t"
                     << "0";
            else if (_arcs[row][col] == _infinity)
                cout << "\t"
                     << ref;
            else
                cout << "\t" << _arcs[row][col];
        }
        cout << endl;
    }
}

template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::SetArcs(int **arcs, int vexNum)
{

    if (vexNum != _vertexes.GetLength())
    {
        cout << "新的邻接矩阵的个数与原图不匹配!" << endl;
        return;
    }
    int arcNum = 0;
    for (int row = 0; row < vexNum; row++)
    {
        for (int col = 0; col < vexNum; col++)
        {
            if (*((int *)arcs + row * vexNum + col) != _infinity)
                arcNum++;
            _arcs[row][col] = *((int *)arcs + row * vexNum + col);
        }
    }
    _arcNum = arcNum / 2;
}

template <class ElemType, class WeightType>
WeightType AdjMatrixGraph<ElemType, WeightType>::GetWeight(int v1, int v2) const
{
    return _arcs[v1][v2];
}

template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
{

    _arcs[v1][v2] = w;
    if (_dirType == 0)
        _arcs[v2][v1] = w;
}

template <class ElemType, class WeightType>
void AdjMatrixGraph<ElemType, WeightType>::Dijkstra(int v)
// 求索引为v的顶点的各个最短路径长度
{
    int _vexNum = _vertexes.GetLength();
    WeightType min;
    WeightType dist[_vexNum]; // 存储当前找到的最短路径长度
    int path[_vexNum];        // 存储目标顶点的直接前驱节点

    for (int i = 0; i < _vexNum; i++)
    {
        dist[i] = _arcs[v][i]; // 存入一条边的路径
        SetTag(i, 0);          // 用_tag表示已经找到最短路径的集合
        if (i != v && dist[i] < _infinity)
            // 若dist[i]存在, 添加前驱节点
            path[i] = v;
        else
            path[i] = -1;
    }
    SetTag(v, 1); //自身已经在集合中

    cout << "所选源点: " << GetElem(v) << endl;

    int finalVex; // 已求出最短路径的顶点
    int w;
    for (int i = 1; i < _vexNum; i++)
    // 按递增序列求最短路径
    {
        min = _infinity;
        finalVex = v;
        for (int j = 0; j < _vexNum; j++)
        // 查询最小的最短路径, 找出finalVex
        {
            if (_tag[j] == 0 && dist[j] < min)
            {
                finalVex = j;
                min = dist[j];
            }
        }
        SetTag(finalVex, 1);
        for (int j = FirstAdjVex(finalVex); j != -1; j = NextAdjVex(finalVex, j))
        // 从上一次找到的最短路径的顶点出发, 依次判断各顶点的最短路径能否更新
        {
            if (_tag[j] == 0 && min + GetWeight(finalVex, j) < dist[j])
            {
                dist[j] = min + GetWeight(finalVex, j);
                path[j] = finalVex;
            }
        }
    }
    // 打印输出
    for (int i = 0; i < _vexNum; i++)
    {
        if (i == v)
            continue;
        string pathStr(1, GetElem(i));

        for (int j = path[i]; j != -1; j = path[j])
        {
            pathStr = string(1, GetElem(j)) + " -> " + pathStr;
        }
        cout << "从顶点 " << GetElem(v) << " 到顶点 " << GetElem(i) << " 的最短路径为: " << pathStr
             << ", 长度为: " << dist[i] << endl;
    }
}

#endif