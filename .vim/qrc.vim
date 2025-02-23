augroup compileAndRun
    "noremap <leader>r :!cmake --build _build --target ProjectCreator 1>/dev/null&&cd _build && rm Test -rf&& ./ProjectCreator --type=cpp --ProjectName="Test" && ls Test<CR>
    noremap <leader>r :!cmake --build _build --target ProjectCreator 1>/dev/null&&cd _build && rm Test -rf && ./ProjectCreator --type=android --ProjectName="Test" --PackageName="com.test.hi" <CR>
augroup END

