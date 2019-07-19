# Huffman
这个文件是对利用Huffman树对文件进行压缩的实现，能完成对英文文章（注意。。。非常遗憾的事情是只能对纯英文文章进行压缩）的压缩和解压。

## encode.cpp
压缩主程序，实现了Huffman树的建立，找到每种字符的二进制编码，输出二进制文件Huffman.compressed和Huffman.config。

## decode.cpp
解压主程序，实现利用Huffman.compressed和Huffman.config生成Huffman树，并解压得到源文件。

## Huffman.compressed
压缩文件，存储了转换后的源文件。

## Huffman.config
配置文件，存储了字符的编码以及源文件中字符的总数。

## source.txt
源文件，存储英文文章


~~~~
~~~~
# 后记
在学期内就编写了Huffman压缩的程序，但当时完成的程序由于压缩后