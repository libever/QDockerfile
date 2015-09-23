#!/bin/sh


cd /root/
gcc -o demo a.c
./demo


git clone https://github.com/gmarik/vundle.git /usr/share/vim/vimfiles/bundle/vundle

cat >> /etc/vimrc <<EOF


"============= ============ =========== custom vim config ============= ============ ============ "

set nu
syntax on
set tabstop=2
set shiftwidth=2
let g:airline_theme='serene'

set hlsearch   
set incsearch " increment search
set showmatch " when keyup the right ) the left ( bright
set background=dark

set nocompatible
filetype on
filetype off

let path='/usr/share/vim/vimfiles/bundle/vundle'
set rtp+=/usr/share/vim/vimfiles/bundle/vundle
call vundle#rc(path)
Plugin 'gmarik/vundle'
Plugin 'Emmet.vim'
Plugin 'scrooloose/nerdtree' 
Plugin 'bling/vim-airline'
Plugin 'fugitive.vim'
Plugin 'hynek/vim-python-pep8-indent'
Plugin 'matchit.zip'
Plugin 'lookupfile' 
Plugin 'genutils' 
Plugin 'bufexplorer.zip'
Plugin 'neocomplcache'
Plugin 'The-NERD-Commenter'
Plugin 'fatih/vim-go'
call vundle#end()

filetype plugin indent on  

set laststatus=2
map <C-n> :NERDTreeToggle<CR>

set modifiable

"autocmd StdinReadPre * let s:std_in=1
"autocmd VimEnter * if argc() == 0 && !exists("s:std_in") | NERDTree | endif

let g:LookupFile_TagExpr = '"./filenametags"' 
let g:LookupFile_PreserveLastPattern = 0 
let g:neocomplcache_enable_at_startup = 1
let g:neocomplcache_enable_auto_select = 1
let g:mapleader = ','

function GRunPython()
	execute "w"
	execute join(["!", " clear && /usr/bin/env python ",bufname("%") ])
endfunction

function PythonFuncList()
	com! -nargs=* RunPython call GRunPython()
	nmap  <Leader><F5> :call GRunPython() <CR>
endfunction
au FileType python call PythonFuncList()


"让vim记忆上次编辑的位置
autocmd BufReadPost *
\ if line("'\"")>0&&line("'\"")<=line("$") |
\	exe "normal g'\"" |
\ endif

colorscheme default

EOF 

ln -s /root/blackhole  /blackhole

