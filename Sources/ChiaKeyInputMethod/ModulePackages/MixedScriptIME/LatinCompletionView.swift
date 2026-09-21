import SwiftUI

@available(macOS 13.0, *)
struct LatinCompletionView: View {
    let completions: [String]
    let onSelect: (String) -> Void
    
    var body: some View {
        VStack(alignment: .leading, spacing: 4) {
            ForEach(Array(completions.enumerated()), id: \.offset) { index, word in
                Button(action: { onSelect(word) }) {
                    HStack {
                        Text("\(index + 1)")
                            .font(.caption)
                            .foregroundColor(.secondary)
                            .frame(width: 20)
                        Text(word)
                            .font(.system(size: 14))
                    }
                    .padding(.horizontal, 8)
                    .padding(.vertical, 4)
                    .frame(maxWidth: .infinity, alignment: .leading)
                    .background(index == 0 ? Color.accentColor.opacity(0.2) : Color.clear)
                    .cornerRadius(4)
                }
            }
        }
        .frame(minWidth: 200, maxWidth: 300)
    }
}

struct LatinCompletionView_Previews: PreviewProvider {
    static var previews: some View {
        LatinCompletionView(completions: ["issue", "issueId", "issueTracker"], onSelect: { _ in })
    }
}
