augroup compileAndRun
    noremap <leader>b :!cmake -H. -B_build -G Ninja -DCMAKE_BUILD_TYPE=Debug <CR>
    noremap <leader>r :!cmake --build _build --target ProjectCreator 1>/dev/null&&cd _build && ./ProjectCreator <CR>
augroup END

