const path = require('path');
const ts = require('gulp-typescript');
const tsProject = ts.createProject('tsconfig.json');

const buildFolder = path.resolve('build');
const tsBuildFolder = path.resolve(buildFolder, 'typescript');
const srcFolder = path.resolve('src');
const tsSrcFolder = path.resolve(srcFolder, "typescript");

gulp.task(
    'copy-rx-in-space',
    gulp.series(
        function(){
            return gulp.src([`${buildFolder}/Debug/*.{node,so}`, `${buildFolder}/Release/*.{node,so}`])
                .pipe(gulp.dest(`${buildFolder}/lib`));
        }
))