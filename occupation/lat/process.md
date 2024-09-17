好的，根据您的要求，我为您编写了一个带有进度条的HTML网页，显示信任值、心动值和感情值，并包含积分制度。您可以根据实际情况更新这些数值。

```html
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>追求进度</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f0f0f0;
        }
        .progress-container {
            width: 80%;
            margin: 20px auto;
        }
        .progress-bar {
            background-color: #ddd;
            border-radius: 5px;
            margin: 20px 0;
            position: relative;
        }
        .progress-bar-inner {
            height: 30px;
            border-radius: 5px;
            line-height: 30px;
            color: #fff;
            text-align: center;
        }
        .trust {
            background-color: #4caf50;
        }
        .heartbeat {
            background-color: #f44336;
        }
        .affection {
            background-color: #2196f3;
        }
        .points {
            background-color: #ff9800;
        }
        h2 {
            text-align: center;
        }
        .update-button {
            display: block;
            margin: 0 auto;
            padding: 10px 20px;
            background-color: #009688;
            color: #fff;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        .update-button:hover {
            background-color: #00796b;
        }
        .value-input {
            width: 50px;
            text-align: center;
        }
        .input-group {
            text-align: center;
            margin: 10px 0;
        }
    </style>
</head>
<body>

<h2>追求进度</h2>
<div class="progress-container">
    <div class="progress-bar">
        <div id="trustBar" class="progress-bar-inner trust" style="width: 0%;">信任值：0%</div>
    </div>
    <div class="progress-bar">
        <div id="heartbeatBar" class="progress-bar-inner heartbeat" style="width: 0%;">心动值：0%</div>
    </div>
    <div class="progress-bar">
        <div id="affectionBar" class="progress-bar-inner affection" style="width: 0%;">感情值：0%</div>
    </div>
    <div class="progress-bar">
        <div id="pointsBar" class="progress-bar-inner points" style="width: 0%;">积分：0</div>
    </div>
</div>

<div class="input-group">
    <label>信任值：<input id="trustInput" class="value-input" type="number" value="0" min="0" max="100"></label>
    <label>心动值：<input id="heartbeatInput" class="value-input" type="number" value="0" min="0" max="100"></label>
    <label>感情值：<input id="affectionInput" class="value-input" type="number" value="0" min="0" max="100"></label>
    <label>积分：<input id="pointsInput" class="value-input" type="number" value="0" min="0"></label>
</div>

<button class="update-button" onclick="updateProgress()">更新进度</button>

<script>
    function updateProgress() {
        var trustValue = parseInt(document.getElementById('trustInput').value);
        var heartbeatValue = parseInt(document.getElementById('heartbeatInput').value);
        var affectionValue = parseInt(document.getElementById('affectionInput').value);
        var pointsValue = parseInt(document.getElementById('pointsInput').value);

        // 确保数值在0到100之间
        trustValue = Math.min(Math.max(trustValue, 0), 100);
        heartbeatValue = Math.min(Math.max(heartbeatValue, 0), 100);
        affectionValue = Math.min(Math.max(affectionValue, 0), 100);

        document.getElementById('trustBar').style.width = trustValue + '%';
        document.getElementById('trustBar').innerText = '信任值：' + trustValue + '%';

        document.getElementById('heartbeatBar').style.width = heartbeatValue + '%';
        document.getElementById('heartbeatBar').innerText = '心动值：' + heartbeatValue + '%';

        document.getElementById('affectionBar').style.width = affectionValue + '%';
        document.getElementById('affectionBar').innerText = '感情值：' + affectionValue + '%';

        document.getElementById('pointsBar').style.width = (pointsValue % 5) * 20 + '%';
        document.getElementById('pointsBar').innerText = '积分：' + pointsValue;

        // 根据规则提示进入下一阶段或其他信息
        if (trustValue >= 100 && heartbeatValue >= 100) {
            alert('恭喜！进入第二个游戏：恋爱游戏。');
        }

        if (affectionValue >= 100) {
            alert('感情值已达100，您可以根据积分制度进行下一步。');
        }
    }
</script>

</body>
</html>
```

**使用说明：**

1. 将上述代码复制并保存为一个以`.html`结尾的文件，例如`progress.html`。
2. 使用浏览器打开该文件。
3. 在页面中，您可以输入当前的信任值、心动值、感情值和积分，然后点击“更新进度”按钮，进度条会根据输入的数值更新。
4. 当信任值和心动值都达到100时，会弹出提示进入第二个游戏。
5. 当感情值达到100时，会提示您可以根据积分制度进行下一步。
6. 积分进度条会以每5分为一个周期显示。

**注意事项：**

- 进度条的数值范围为0到100，请确保输入的数值在此范围内。
- 您可以根据需要修改和扩展此代码，例如添加更多的互动元素或美化页面。

希望这个网页能帮助您直观地查看追求进度，祝您一切顺利！