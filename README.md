## 服务监控助手 By Kingtous

> 作者：[Kingtous](https://kingtous.cn)
>
> Github: [Kingtous](https://github.com/Kingtous)
>
> 源码地址：[Gitee](https://gitee.com/kingtous/service-monitor-dtk)

![](https://file.kingtous.cn/index.php?user/publicLink&fid=b6f5lIH6AsjtLB7nX7p9SFV4rintocx-6YZWbgqPyavesti9FC9Z44QUTsk0jL7N_4ayud6G_qKpL2oNtJ-8jGtvItZOv8CvMa1P6EC9l_Jsx_tZ4QRtRv8dBhyBXW8f3HUKSFEHlkSUL6QxDmAW&file_name=/recording.gif)

### 简介

可用于监控各类URL，定制化监控需求（定时，定量），保障API稳定。

![](https://file.kingtous.cn/index.php?user/publicLink&fid=1c1c_rrZnjz4FVLVvMrOnpZRnhzQgNCzs6XKqUl1dUDRWVDxCtDL54lHOzeW9WtYmtz9mzQbQ15p3QF9syOROdpBPrQum5RWm7a-vcySffTrw8f9zcb0HLLSufp-dH1QgiGkD6I3VVgT_9_Ig4zMqTNMCAp5OU58H6GZOr12XEuNBPGkg4T9OA&file_name=/%E6%88%AA%E5%9B%BE_%E9%80%89%E6%8B%A9%E5%8C%BA%E5%9F%9F_20211030115414.png)

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

> 暂时没有龙芯虚拟机，故现只提供amd64, arm64下载地址

[码云下载](https://gitee.com/kingtous/service-monitor-dtk/releases)

### 使用截图与帮助

##### 添加监控记录

- 在右上角添加完组后，可以在设置页面右击组，可以添加服务，设置如下

![](https://file.kingtous.cn/index.php?user/publicLink&fid=f7e2L8lqdCnGlI1hKAYVdXER3YfgCMLc55oqxjoC_mv7r1aqADq3GNqfqf4dL6xubfdvmzMbj-3ItVl5YFR4Cw9f4fPj1KcoRyYmq9Q76KEXvkOINDM-1-uTEXCY5c8CIv0RiaDpMeV7f2ukYdgG5sb3yPiie6SDgF1kINrYe8XAto-aggxfFm-UoQ&file_name=/%E6%88%AA%E5%9B%BE_service_monitor_20211030115512.png)

##### 组详情面板

点击详情按钮后，出现监控面板

> 若延迟线在顶部，说明可能出现了访问错误（大多数是超时），可以在主窗口中观察具体延迟信息

![](https://file.kingtous.cn/index.php?user/publicLink&fid=46c4VzarQlk7QGbEoFsKD7k9Zf39zO3xLMYXG_qwnS36RMX8ygAbnOpMs8NG1EZ1XeorPIoSu1lajuM71f2xta9i8KBAFTgnA-Yy0ltVMhFSPoTV01MDmWGVbgPneNNlxHLxk_Msd3iimMxcbZiFdXdnWhqLhN4pdLjgfLB4sDY3kYfD59003A&file_name=/%E6%88%AA%E5%9B%BE_%E9%80%89%E6%8B%A9%E5%8C%BA%E5%9F%9F_20211030111446.png)

##### 查看日志

目前**暂时**可通过查看日志的方式查看所有监控信息，按钮如下：

![](https://file.kingtous.cn/index.php?user/publicLink&fid=6a18ogvcPBxl4mokiIeYWZNruJaYH86O_VkRsNuNu5EXlPnwgEQKaf7p9JL1BgczMI4yi46PhUgBOGPhDV8NPIhsQnbErN4FK0bxxB5CEe63_BVrSYlud9pMeoFrvv3VKbdxQT3sM8FJuzl_4zAQEbiakS664hnO-tu05cFcKBUhsQ-QazkrxCMSRg&file_name=/%E6%88%AA%E5%9B%BE_service_monitor_20211030115545.png)

日志格式如下：

格式统一，可以使用Python等数据分析软件对延迟进行可视化。

![](https://file.kingtous.cn/index.php?user/publicLink&fid=ba20zVDsWkj4-mW_2x5wwDlAxMAkVQ9h5mP1A5xzFaRSpbuA6Z1PzZyT8Gwc2hhgNBP97x7bnTk-3M49yL_IF1CRxvWMywr7BiyhmmEnAHsZhZoWEAewhpELZskKiOYIg997fI9qNm8cLrcM4lK2dmoOdK4D-abl1pGvi6M78BEaZWsCh1isG6wIeg&file_name=/%E6%88%AA%E5%9B%BE_deepin-terminal_20211030121722.png)

### TODOs

- 超过设定超时次数报警（可配置qq邮箱等接收报警次数）
- 目前使用日志记录历史延迟信息，还没有导出excel表格功能

