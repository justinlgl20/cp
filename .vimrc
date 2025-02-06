set number
set smartindent
set tabstop=8
set mouse=a
set shiftwidth=8
set showcmd

imap jk <Esc>
inoremap {<CR> {<CR>}<Esc>O

autocmd filetype cpp nnoremap <C-H> :w !g++ -W -o %:r %:r.cpp -DDEBUG <CR>
autocmd filetype cpp nnoremap <C-J> :!./%:r < in.txt <CR>
nnoremap <C-K> :!cat > in.txt <CR>
