augroup compileAndRun
    noremap <leader>r :!cmake --build _build --target AndroidProjectCreator 1>/dev/null&&cd _build && ./AndroidProjectCreator --type=android --ProjectName="Test" --packageName="com.test.hi" && cat t/df<CR>
augroup END

