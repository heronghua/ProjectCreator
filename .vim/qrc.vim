augroup compileAndRun
    noremap <leader>r :!cmake --build _build --target ProjectCreator 1>/dev/null&&cd _build && ./ProjectCreator --type=android --ProjectName="Test" --packageName="com.test.hi" && cat t/df<CR>
augroup END

