## 服务监控助手 By Kingtous

> 作者：[Kingtous](https://kingtous.cn)
>
> Github: [Kingtous](https://github.com/Kingtous)
>
> 源码地址：[Gitee](https://gitee.com/kingtous/service-monitor-dtk)

![](https://file.kingtous.cn/index.php?user/publicLink&fid=0cdeAHSiA18fM848ijecJEYkN3oQ83dVhcDG-MgDbmhal8L2t8YM27pEKJ6WifkfFFgE-TKNbOiUdWk8r9Th24ErNeef59tw5SjtZcKL1pcnmfMhjrYcb3pcqZOO3RngXI0hVdghGX96OKE&file_name=/recording.gif)

### 简介

可用于监控各类URL，定制化监控需求（定时，定量），保障API稳定。

![](https://file.kingtous.cn/index.php?user/publicLink&fid=51e84KX0jOd0C5peEMgKecOMauWaGprew_xv84EszhSGPdUzhlxBovUFtmg8PQsNyRXXmjyMsEC-aX5C7BfBmksh82vvs51tblZEVA9HfdwAhKdbQj5lcVUlZMpoefxYd0YWKTUU3UItmldUWmkQiiilGJs0eUxC1ASwnymCPZz8A7S7&file_name=/%E6%88%AA%E5%9B%BE_%E9%80%89%E6%8B%A9%E5%8C%BA%E5%9F%9F_20211030115414.png)

### 特性

- 使用美观的DTK（Deepin Tool Kit）进行界面绘制
- 极具吸引力的**动画监控窗格**
- 分组监控，每组延迟清晰可见
- 主界面合并所有延迟信息，绘制成线，实时查看整体情况
- 实时记录日志，用户可轻松导出日志
- 丰富的帮助信息
- 相比java、python程序，占用较低的监控程序，轻松满足低配置场景

### 场景示例

- 每半分钟发送TCP/UDP请求给服务器，检测服务器是否正常工作
- 统计一天内服务端API的延迟情况

### 下载地址

> 暂时没有龙芯虚拟机，故现只提供amd64、arm64下载地址

[码云下载](https://gitee.com/kingtous/service-monitor-dtk/releases)

### 使用截图与帮助

##### 添加监控记录

- 在右上角添加完组后，可以在设置页面右击组，可以添加服务，设置如下

![](https://file.kingtous.cn/index.php?user/publicLink&fid=b9a4hzALBzoVoEOAGJXHXn1NBKNuh5Ccd1thonaQTPArs28L_gt4d3D2fOEivtqpc-5hDh2lkjnnIp8Lh58s5CJGg2KeIp3qCGHB-QNj1zh5VQ4X38JzlYygUcFSUWQSxeVPJmR-Whiuj4I6HcLSnyF2a9AcJgdIfRzpqvn7pPhoL9r68R5R&file_name=/%E6%88%AA%E5%9B%BE_service_monitor_20211030115512.png)

##### 组详情面板

点击详情按钮后，出现监控面板

> 若延迟线在顶部，说明可能出现了访问错误（大多数是超时），可以在主窗口中观察具体延迟信息

![](https://file.kingtous.cn/index.php?user/publicLink&fid=8fc1xWRoQfxwdCCqclH57pO-4N-4R1OcwwaJXGW2I15OomWOJBbXYwWXQ1-WBAvqErezUVMRHyxFsTqnfXS5eDPji0v_iCQzcph35P5ZhiGRSrVQXlPnIcCw78_JjphDC8mKDe4E97kz5hljMZlel21FBac0d-IdrFCLYZtdfhDCI_xT&file_name=/%E6%88%AA%E5%9B%BE_%E9%80%89%E6%8B%A9%E5%8C%BA%E5%9F%9F_20211030111446.png)

##### 查看日志

目前**暂时**可通过查看日志的方式查看所有监控信息，按钮如下：

![](https://file.kingtous.cn/index.php?user/publicLink&fid=dcc1dezW-l7OG5IB37yHOCiO172sTtxOtGffxxZTlOtVaiYAIVKySYtKz0U2-SQD1BT_tKhFmy8udA99FbAp_LJwKCA3X-v9B5EKqhz6uzZVNbzY7wCfSv-7VYhmY3WFzal1lB6r1U87g-LLNf7jf-OdDYgyXxKDOst-cEp6LuaEcHTS-Ycb&file_name=/%E6%88%AA%E5%9B%BE_service_monitor_20211030115545.png)

日志格式如下：

格式统一，可以使用Python等数据分析软件对延迟进行可视化。

![](https://file.kingtous.cn/index.php?user/publicLink&fid=d74fQKynEnrL8D0K6_NRycU0W-AFyqXLqN6RoZOmoPQQdIm-2iduVx69HRgFf9XUN2pip_A2FHJZVARHFAGnb4-I1Q3xwmkyuWLnDCBILJqRt1g-eLfXn6K6fX5p4Ofv9Ch2IeRD4w7AccthllAajp0t5fKyDxwtCFT-ToO_x59Wt7LLSsfX&file_name=/%E6%88%AA%E5%9B%BE_deepin-terminal_20211030121722.png)

### TODOs

- 超过设定超时次数报警（可配置qq邮箱等接收报警次数）
- 目前使用日志记录历史延迟信息，还没有导出excel表格功能

