# UART DMA / DMA IDLE

```C
HAL_UARTEx_ReceiveToIdle_DMA(&huart5, RxBuf, RxBuf_SIZE);
__HAL_DMA_DISABLE_IT(&hdma_uart5_rx, DMA_IT_HT);
```
