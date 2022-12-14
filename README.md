# TETRIS
どっかのソースコードコピペして、改造したものです。<br>
アルゴリズムをちょっとくらい考えたんですが、やっぱりめんどくさかったのでコピペして改造することにしました。（´・ω・｀）

## インストール
```
$ sudo apt install libncurses5-dev libncursesw5-dev ncurses-doc libsdl-mixer1.2-dev
$ git clone https://github.com/ware255/tetris.git
$ cd tetris
$ gcc main.c -o tetris -lncurses -lSDL_mixer
$ ./tetris
```

## 遊び方
引数を適当につけて実行させると遊び方がわかります。<br>
例 `$ ./tetris --help`

## 見た目
![見た目](https://github.com/ware255/tetris/blob/main/tetris.gif)

## 参考にさせていただいたもの
[テトリス](https://ja.wikipedia.org/wiki/%E3%83%86%E3%83%88%E3%83%AA%E3%82%B9)<br>
[【C言語】ncursesの使い方【ゲーム，テトリス，ブロック崩し】](https://hiroyukichishiro.com/ncurses-in-c-language/?PageSpeed=noscript)<br>
[ncurses](http://kis-lab.com/serikashiki/man/ncurses.html)<br>
[curses による端末制御](https://www.kushiro-ct.ac.jp/yanagawa/ex-2017/2-game/01.html)<br>
[ゲームプログラミング：C++でテトリスを作ってみた](https://qiita.com/Chomolungma/items/52bd8b133b747cb603e7)<br>
[SDL プログラミング](http://netadm.iss.tokushima-u.ac.jp/soft/dev/SDL.pdf)<br>
