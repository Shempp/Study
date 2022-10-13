# Render Queue

## Task description

Need to develop a two-threaded render queue

The main game thread (`MainThread`) inserts commands (with parameters) into the render command queue, which are processed in the graphics thread (`GraphicsThread`). The graphics thread, in turn, reads these commands and processes them.

1. It is necessary to be able to wait for the execution of all current commands from the main thread (`Flush` operation).
2. You need to be able to wait for the execution of commands from the main thread and reset the queue (`Reset` operation).

**The command queue must be written using semaphores and atomics (using a mutex is impractical for performance reasons).**

An example of what the API looks like:

```cpp
class CRenderQueue
{
public:
	void AddCommand(eRqCommand cmd);
	void AddUint32(uint32 value);

	void AddData(const char* data, size_t size);

	uint32 ReadValue();
	const char* ReadData(size_t& size);
}
```

**Important: the system must be fault-tolerant to any kind of errors and exceptions, no crashes.**

As test commands, you can print a message to the console or `beep(Beep(50, 50))` `winapi`.