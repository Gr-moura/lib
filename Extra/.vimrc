" Netrw settings
let g:netrw_liststyle = 3

" Line numbers
set relativenumber " Show relative line numbers
set number " Show absolute line number on the cursor line when relative number is on

" Tabs and indentation
set tabstop=4 " 4 spaces for tabs
set shiftwidth=4 " 4 spaces for indent width
set autoindent " Copy indent from current line when starting a new one

" Line wrapping
set nowrap " Disable line wrapping

" Search settings
set ignorecase " Ignore case when searching
set smartcase " If search includes mixed case, assume case-sensitive

" Cursor line
set cursorline " Highlight the current cursor line

" Appearance
set termguicolors " Enable true color support
set background=dark " Set background to dark for compatible colorschemes
" set signcolumn=yes " Always show the sign column

" Backspace
set backspace=indent,eol,start " Allow backspace in insert mode

" Clipboard
set clipboard+=unnamedplus " Use the system clipboard as default register

" Split windows
set splitright " Split vertical windows to the right
set splitbelow " Split horizontal windows to the bottom

" Disable swapfile
set noswapfile

" Desativa sons e alertas visuais
set noerrorbells " Desativa o som de erro
" set novisualbell " Desativa o alerta visual (flash da tela)
" set t_vb= " Remove qualquer configuração de alerta visual
set belloff=all " Desativa todos os tipos de campainha

" Set leader key to space
let mapleader = " "

" Use 'jk' to exit insert mode
inoremap jk <ESC>

" Have j and k navigate visual lines rather than logical ones
nmap j gj
nmap k gk

" I like using H and L for beginning/end of line
nmap H ^
nmap L $

" Clear search highlights
nnoremap <leader>nh :nohl<CR>

" Melhorias no comportamento do comando Y
nnoremap Y yg$

" Melhorias na navegação com 'n' e 'N'

" Mantém a busca centralizada ao avançar (n)
nnoremap n nzzzv

" Mantém a busca centralizada ao retroceder (N)
nnoremap N Nzzzv

" Melhorias ao juntar linhas
" nnoremap J mzJ`z  " Junta a linha abaixo sem mover o cursor inesperadamente

" Melhorias na rolagem
nnoremap <C-d> <C-d>zz  " Move meia página para baixo e mantém o cursor centralizado
nnoremap <C-u> <C-u>zz  " Move meia página para cima e mantém o cursor centralizado

" Cola sobre um texto sem sobrescrever o registro de cópia
xnoremap <leader>p "_dP

" Copiar para o clipboard do sistema
nnoremap <leader>y "+y
vnoremap <leader>y "+y
nmap <leader>Y "+Y

" Deletar sem salvar no registro padrão (não sobrescreve o yank)
nnoremap <leader>d "_d   " Deleta sem copiar
vnoremap <leader>d "_d   " Deleta a seleção sem copiar

" Increment/decrement numbers
nnoremap <leader>+ <C-a> " Increment number
nnoremap <leader>- <C-x> " Decrement number


" Replace the word under cursor in the entire file
nnoremap <leader>s :%s/\<<C-r><C-w>\>/<C-r><C-w>/gI<Left><Left><Left>

" Make the current file executable
nnoremap <leader>x :!chmod +x %<CR>

" Window management
nnoremap <leader>sv <C-w>v " Split window vertically
nnoremap <leader>sh <C-w>s " Split window horizontally
nnoremap <leader>se <C-w>= " Make splits equal size
nnoremap <leader>sx :close<CR> " Close current split

" Tab management
nnoremap <leader>to :tabnew<CR> " Open new tab
nnoremap <leader>tx :tabclose<CR> " Close current tab
nnoremap <leader>tn :tabn<CR> " Go to next tab
nnoremap <leader>tp :tabp<CR> " Go to previous tab
nnoremap <leader>tf :tabnew %<CR> " Open current buffer in new tab

" Save file
nnoremap <F3> :w<CR>
inoremap <F3> <ESC>:w<CR>

" Copy all
nnoremap <leader>ca :%y+<CR>

" Map CTRL+h, CTRL+j, CTRL+k, CTRL+l to arrow keys in Insert mode
inoremap <C-h> <Left>
inoremap <C-j> <Down>
inoremap <C-k> <Up>
inoremap <C-l> <Right>

" Optional: Disable the actual arrow keys if you want to enforce using CTRL+hjkl
" inoremap <Up> <NOP>
" inoremap <Down> <NOP>
" inoremap <Left> <NOP>
" inoremap <Right> <NOP>

" Disable arrow keys in Visual mode
" vnoremap <Up> <NOP>
" vnoremap <Down> <NOP>
" vnoremap <Left> <NOP>
" vnoremap <Right> <NOP>

" Disable arrow keys in Normal mode
" nnoremap <Up> <NOP>
" nnoremap <Down> <NOP>
" nnoremap <Left> <NOP>
" nnoremap <Right> <NOP>
