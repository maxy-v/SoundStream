# SoundStream
Easy to use sound stream class for Qt projects. All you need to do is to connect it with your audio generating function.

```C++
connect(&stream, &SoundStream::dataRequired, your_object, &YourObject::generateData);
```

And then call its start, pause and stop methods.
