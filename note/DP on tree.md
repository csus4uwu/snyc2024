树形DP
===

题单来自：https://www.luogu.com.cn/training/11363#problems

[toc]

## 没有上司的舞会

某大学有 $n$ 个职员，每个员工有快乐值 $r_i$。

他们的从属关系可以构成一棵树，树的结构为：**上司 $\rightarrow$ 下属**。

有一个宴会，如果邀请一个人的（直接）上司，这个人就不会来。问最大的总快乐值。

<details>

设 $f_{i, j}$ 为以 $i$ 为根的子树，且 $i$ **参加（ $j=1$ ）/不参加（ $j=0$ ）** 宴会时，最大的快乐值，初始时 $f_{i, 1}=r_i$。

对于 $u\rightarrow v$，更新完 $v$ 后有

$$
\begin{align*}
f_{u, 1} &\leftarrow f_{u, 1} + f_{v, 0} \\
f_{u, 0} &\leftarrow f_{u, 0} + \max\{f_{v, 1}, f_{v, 0}\}
\end{align*}
$$

</details>

## 二叉苹果树

给一棵二叉树，每条边上有一些苹果。

问保留 $q$ 条边的情况下，最多能留多少苹果。

<details>

设 $f_{i, j}$ 为以 $i$ 为根的子树，保留 $j$ 条边的情况下的最优答案。

对于 $u\stackrel{w}\longrightarrow v$，更新完 $v$ 后有

$$
\begin{align*}
f_{u, i} &= \max\{f_{u, i}, f_{u, i - j - 1} + f_{v, j} + w\}\\ &i:q\rightarrow0，j:i-1\rightarrow0
\end{align*}
$$

转移类似背包，舍弃 $j + 1$ 条边（因为和子节点也是一条边），拿子树留 $j$ 条边的答案。

</details>

## 最少点覆盖问题

### [战略游戏](https://www.luogu.com.cn/problem/P2016)

一棵无根树，如果一个节点有士兵，那么与该节点相连的所有**边**都能被看到。

问最少需要站几个士兵，让所有**边**都能被看到。

### [保安站岗](https://www.luogu.com.cn/problem/P2458)

一棵无根树，如果一个节点有保安，那么与该节点相连的所有**节点**都能被看到。

每个节点站保安需要花费 $c_i$。

问最少需要花多少钱，让所有**节点**都能被看到。

<details>

- 战略游戏：状态设计和转移同**没有上司的舞会**，不再赘述。

- 保安站岗：即上题题面中**边**改为**节点**，那么可以设置三个维度的状态：$f_{i, j}$ 表示 $i$ 为根的子树，且 $i$ **被儿子覆盖（$j=0$）/ 被自己覆盖（$j=1$）/ 被父亲覆盖（$j = 2$）** 时的最优答案，初始时 $f_{i, 1}=c_i$。

    对于 $u\rightarrow v$，更新完 $v$ 后有

    $$
    \begin{align}
    f_{u, 0}&\leftarrow f_{u, 1}+\min_{i = 0, 1} f_{v, i}\  (\Delta) \\
    f_{u, 1}&\leftarrow f_{u, 1}+\min_{i = 0, 1, 2} f_{v, i}\\
    f_{u, 2}&\leftarrow f_{u, 1}+\min_{i = 0, 1} f_{v, i}
    \end{align}
    $$

    $\Delta$：特别地，对于 $f_{u, 0}$，须**至少取一个** $f_{v, 1}$。在实现层面，可以记录是否取过，并记录 $f_{v, 1}-f_{v, 0}$ 的最小值 $\rm cost$，若最终没有取过，说明每个 $f_{v, 1}$ 都大于 $f_{v, 0}$，那么加上 $\rm cost$ 即可。该转移的核心代码如下。

    ```cpp
    auto dfs = [&](auto self, int u, int fa) -> void {
        int cost{inf};
        bool flag{};

        for (int v : adj[u]) {
            ...
            dp[u][0] += min(dp[v][0], dp[v][1]);

            if (dp[v][0] < dp[v][1]) {
                cost = min(cost, dp[v][1] - dp[v][0]);
            } else {
                flag = true;
            }
            ...
        }
        if (not flag) {
            dp[u][0] += cost;
        }
    };
    ```

</details>