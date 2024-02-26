require 'rspec'

RSpec.describe "My BC" do
    before :all do
        QwasarRspec.make
        QwasarRspec.make_fclean("./my_bc")
        QwasarRspec.make
        QwasarRspec.check_forbidden_functions(['system', 'execl', 'execlp', 'execvp', 'execvP'], "./my_bc")
    end

    it 'Simple test 0#' do
        stdout_user, stderr_user, _ = QwasarRspec.execute("./my_bc", 1)
        expect(stdout_user).to eq("1\n")
    end

    it 'Simple test 1#' do
        stdout_user, stderr_user, _ = QwasarRspec.execute("./my_bc", "1 + 1")
        expect(stdout_user).to eq("2\n")
    end

    it 'Simple test 2#' do
        stdout_user, stderr_user, _ = QwasarRspec.execute("./my_bc", "1+2*(3-42)%5")
        expect(stdout_user).to eq("-2\n")
    end

    it 'Simple test 3#' do
        stdout_user, stderr_user, _ = QwasarRspec.execute("./my_bc", "15/4")
        expect(stdout_user).to eq("3\n")
    end

    it 'Simple test 4#' do
        stdout_user, stderr_user, _ = QwasarRspec.execute("./my_bc", "1 - 9 + 9")
        expect(stdout_user).to eq("1\n")
    end

    it 'Error management test 0#' do
        stdout_user, stderr_user, status = QwasarRspec.execute("./my_bc", "312/0")
        expect(stderr_user.downcase).to include("divide by zero")
        expect(status.exitstatus).to eq(1)
    end

    it 'Error management test 1#' do
        stdout_user, stderr_user, status = QwasarRspec.execute("./my_bc", "1+/+2")
        expect(stderr_user.downcase).to include("parse error")
        expect(status.exitstatus).to eq(1)
    end

    it 'Error management test 2#' do
        stdout_user, stderr_user, status = QwasarRspec.execute("./my_bc", "321()")
        expect(stderr_user.downcase).to include("parse error")
        expect(status.exitstatus).to eq(1)
    end

    it 'Error management test 3#' do
        stdout_user, stderr_user, status = QwasarRspec.execute("./my_bc", "1+bonjour")
        expect(stderr_user.downcase).to include("parse error")
        expect(status.exitstatus).to eq(1)
    end
end
