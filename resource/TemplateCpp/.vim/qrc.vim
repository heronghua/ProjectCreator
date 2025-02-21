augroup compileAndRun
    noremap <leader>r :!cmake --build _build --target ProjectCreator 1>/dev/null&&cd _build && ./ProjectCreator <CR>
augroup END

