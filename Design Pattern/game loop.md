```cpp
while (true) {
    processInput();
    update();
    render();
}

```

## thời gian cố định

```cpp
const double MS_PER_FRAME = 16.67; // 60 FPS
while (true) {
    double start = getCurrentTime();
    processInput();
    update();
    render();
    sleep(start + MS_PER_FRAME - getCurrentTime());
}
```