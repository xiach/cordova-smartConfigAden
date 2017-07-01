# 配网配置

## 启动配网配置

```
window.smart.start({
    ssid: ""    // 配网的名称 
    pswd: ""    // 配网的密码
}, 
function(successResults){
        alert(successResults)
}, 
function(errorResults){
        alert(errorResults) // 不管什么错误，直接弹出提示下面的语句↓
});
返回成功样例:{"code":"success","mac":"11:xx:L1:12:ss:ss"}
其他都是错误，直接前端提示:配网失败,请检查网络和帐号密码是否正确
```

## 获取ssid名称

```
特别提示：没有连接wifi 这里的配网是不会成功，所以判断下 获取的wifi名字出错了
则提交配网请求，直接提示他 要连接wifi才给配网
window.smart.wifiSsid({}, 
function(successResults){
        alert(successResults)
}, 
function(errorResults){
        alert(errorResults) // 错误提示 请打开或者连接wifi↓
});
返回成功样例:{"code":"success","ssid":"xxx"}
```

## 取消配网

```
停止当前的配网动作
window.smart.stop({}, 
function(successResults){
        alert(successResults)
}, 
function(errorResults){
        alert(errorResults) // 错误提示 请打开或者连接wifi↓
});
返回成功样例:{"code":"success"}
```

## 注

1. 插件超时不会提供消息(sdk没有这个功能)，
2. 按照萝卜的提供直接页面展示60秒计时,60秒还未返回消息，直接返回错误提示语